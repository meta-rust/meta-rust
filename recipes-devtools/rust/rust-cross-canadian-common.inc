
RUST_ALTERNATE_EXE_PATH = "${STAGING_LIBDIR_NATIVE}/llvm-rust/bin/llvm-config"

require rust-target.inc

inherit cross-canadian

DEPENDS += "  \
            virtual/${HOST_PREFIX}gcc-crosssdk \
            virtual/nativesdk-libc rust-llvm-native \
            virtual/${TARGET_PREFIX}compilerlibs \
            virtual/nativesdk-${HOST_PREFIX}compilerlibs \
            gcc-cross-${TARGET_ARCH} \
           "

# The host tools are likely not to be able to do the necessary operation on
# the target architecturea. Alternatively one could check compatibility
# between host/target.
EXCLUDE_FROM_SHLIBS_${RUSTLIB_TARGET_PN} = "1"

DEBUG_PREFIX_MAP = "-fdebug-prefix-map=${WORKDIR}=/usr/src/debug/${PN}/${EXTENDPE}${PV}-${PR} \
                    -fdebug-prefix-map=${STAGING_DIR_HOST}= \
                    -fdebug-prefix-map=${STAGING_DIR_NATIVE}= \
                    "

LLVM_TARGET[x86_64] = "${RUST_HOST_SYS}"
python do_rust_gen_targets () {
    wd = d.getVar('WORKDIR') + '/targets/'
    rust_gen_target(d, 'TARGET', wd, d.getVar('TARGET_LLVM_FEATURES') or "", d.getVar('TARGET_LLVM_CPU'), d.getVar('TARGET_ARCH'))
    rust_gen_target(d, 'HOST', wd, "", "generic", d.getVar('HOST_ARCH'))
    rust_gen_target(d, 'BUILD', wd, "", "generic", d.getVar('BUILD_ARCH'))
}

INHIBIT_DEFAULT_RUST_DEPS = "1"

export TARGET_CC = "${CCACHE}${TARGET_PREFIX}gcc --sysroot=${STAGING_DIR_TARGET} ${TARGET_CC_ARCH} ${SECURITY_NOPIE_CFLAGS}"
export TARGET_CXX = "${CCACHE}${TARGET_PREFIX}g++ --sysroot=${STAGING_DIR_TARGET} ${TARGET_CC_ARCH} ${SECURITY_NOPIE_CFLAGS}"
export TARGET_CCLD = "${TARGET_PREFIX}gcc --sysroot=${STAGING_DIR_TARGET} ${TARGET_CC_ARCH} ${SECURITY_NOPIE_CFLAGS}"
export TARGET_AR = "${TARGET_PREFIX}ar"

do_rust_create_wrappers () {
	mkdir -p "${WRAPPER_DIR}"

	# Yocto Build / Rust Host C compiler
	create_wrapper "${RUST_BUILD_CC}" "${BUILD_CC}"
	# Yocto Build / Rust Host C++ compiler
	create_wrapper "${RUST_BUILD_CXX}" "${BUILD_CXX}"
	# Yocto Build / Rust Host linker
	create_wrapper "${RUST_BUILD_CCLD}" "${BUILD_CCLD}" "${BUILD_LDFLAGS}"
	# Yocto Build / Rust Host archiver
	create_wrapper "${RUST_BUILD_AR}" "${BUILD_AR}"

	# Yocto Target / Rust Target C compiler
	create_wrapper "${RUST_TARGET_CC}" "${TARGET_CC}"
	# Yocto Target / Rust Target C++ compiler
	create_wrapper "${RUST_TARGET_CXX}" "${TARGET_CXX}"
	# Yocto Target / Rust Target linker
	create_wrapper "${RUST_TARGET_CCLD}" "${TARGET_CCLD}" "${TARGET_LDFLAGS}"
	# Yocto Target / Rust Target archiver
	create_wrapper "${RUST_TARGET_AR}" "${TARGET_AR}"
}

python do_configure() {
    import json
    from distutils.version import LooseVersion
    try:
        import configparser
    except ImportError:
        import ConfigParser as configparser

    # toml is rather similar to standard ini like format except it likes values
    # that look more JSON like. So for our purposes simply escaping all values
    # as JSON seem to work fine.

    e = lambda s: json.dumps(s)

    config = configparser.RawConfigParser()

    # [target.ARCH-poky-linux]
    target_section = "target.{}".format(d.getVar('TARGET_SYS', True))
    config.add_section(target_section)

    llvm_config = d.expand("${YOCTO_ALTERNATE_EXE_PATH}")
    config.set(target_section, "llvm-config", e(llvm_config))

    config.set(target_section, "cxx", e(d.expand("${RUST_TARGET_CXX}")))
    config.set(target_section, "cc", e(d.expand("${RUST_TARGET_CC}")))
    config.set(target_section, "ar", e(d.expand("${RUST_TARGET_AR}")))

    # If we don't do this rust-native will compile it's own llvm for BUILD.
    # [target.${BUILD_ARCH}-unknown-linux-gnu]
    target_section = "target.{}".format(d.getVar('SNAPSHOT_BUILD_SYS', True))
    config.add_section(target_section)

    config.set(target_section, "llvm-config", e(llvm_config))

    config.set(target_section, "cxx", e(d.expand("${RUST_BUILD_CXX}")))
    config.set(target_section, "cc", e(d.expand("${RUST_BUILD_CC}")))
    config.set(target_section, "ar", e(d.expand("${RUST_BUILD_AR}")))

    # [rust]
    config.add_section("rust")
    config.set("rust", "rpath", e(True))
    config.set("rust", "channel", e("stable"))

    if LooseVersion(d.getVar("PV")) < LooseVersion("1.32.0"):
        config.set("rust", "use-jemalloc", e(False))

    # Whether or not to optimize the compiler and standard library
    config.set("rust", "optimize", e(True))

    # [build]
    config.add_section("build")
    config.set("build", "submodules", e(False))
    config.set("build", "docs", e(False))

    rustc = d.expand("${WORKDIR}/rust-snapshot/bin/rustc")
    config.set("build", "rustc", e(rustc))

    cargo = d.expand("${WORKDIR}/rust-snapshot/bin/cargo")
    config.set("build", "cargo", e(cargo))

    config.set("build", "vendor", e(True))

    targets = [d.getVar("TARGET_SYS", True), "{}-unknown-linux-gnu".format(d.getVar("HOST_ARCH", True))]
    config.set("build", "target", e(targets))

    hosts = ["{}-unknown-linux-gnu".format(d.getVar("HOST_ARCH", True))]
    config.set("build", "host", e(hosts))

    # We can't use BUILD_SYS since that is something the rust snapshot knows
    # nothing about when trying to build some stage0 tools (like fabricate)
    config.set("build", "build", e(d.getVar("SNAPSHOT_BUILD_SYS", True)))

    # [install]
    config.add_section("install")
    # ./x.py install doesn't have any notion of "destdir"
    # but we can prepend ${D} to all the directories instead
    config.set("install", "prefix",  e(d.getVar("D", True) + d.getVar("prefix", True)))
    config.set("install", "bindir",  e(d.getVar("D", True) + d.getVar("bindir", True)))
    config.set("install", "libdir",  e(d.getVar("D", True) + d.getVar("libdir", True)))
    config.set("install", "datadir", e(d.getVar("D", True) + d.getVar("datadir", True)))
    config.set("install", "mandir",  e(d.getVar("D", True) + d.getVar("mandir", True)))

    with open("config.toml", "w") as f:
        f.write('changelog-seen = 2\n\n')
        config.write(f)

    # set up ${WORKDIR}/cargo_home
    bb.build.exec_func("setup_cargo_environment", d)
}

INSANE_SKIP_${RUSTLIB_TARGET_PN} = "file-rdeps arch ldflags"
SKIP_FILEDEPS_${RUSTLIB_TARGET_PN} = "1"

INHIBIT_PACKAGE_DEBUG_SPLIT = "1"
INHIBIT_PACKAGE_STRIP = "1"
INHIBIT_SYSROOT_STRIP = "1"

