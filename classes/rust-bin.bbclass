inherit rust

RUSTLIB_DEP ?= " rustlib"
DEPENDS .= "${RUSTLIB_DEP}"
RDEPENDS_${PN} .= "${RUSTLIB_DEP}"
DEPENDS += "patchelf-native"

export rustlibdir = "${libdir}/rust"
FILES_${PN} += "${rustlibdir}/*.so"
FILES_${PN}-dev += "${rustlibdir}/*.rlib"
FILES_${PN}-dbg += "${rustlibdir}/.debug"

RUSTC_ARCHFLAGS += "-C opt-level=3 -g -L ${STAGING_DIR_HOST}/${rustlibdir}"
EXTRA_OEMAKE += 'RUSTC_ARCHFLAGS="${RUSTC_ARCHFLAGS}"'

# Some libraries alias with the standard library but libstd is configured to
# make it difficult or imposisble to use its version. Unfortunately libstd
# must be explicitly overridden using extern.
OVERLAP_LIBS = "\
    libc \
    log \
    getopts \
    rand \
"
def get_overlap_deps(d):
    deps = d.getVar("DEPENDS", True).split()
    overlap_deps = []
    for o in d.getVar("OVERLAP_LIBS", True).split():
        l = len([o for dep in deps if (o + '-rs' in dep)])
        if l > 0:
            overlap_deps.append(o)
    return " ".join(overlap_deps)
OVERLAP_DEPS = "${@get_overlap_deps(d)}"

# Prevents multiple static copies of standard library modules
# See https://github.com/rust-lang/rust/issues/19680
RUSTC_PREFER_DYNAMIC = "-C prefer-dynamic"
RUSTC_FLAGS += "${RUSTC_PREFER_DYNAMIC}"

rustlib_suffix="${TUNE_ARCH}${TARGET_VENDOR}-${TARGET_OS}/rustlib/${HOST_SYS}/lib"
# Native sysroot standard library path
rustlib_src="${prefix}/lib/${rustlib_suffix}"
# Host sysroot standard library path
rustlib="${libdir}/${rustlib_suffix}"
CRATE_NAME ?= "${@d.getVar('BPN', True).replace('-rs', '').replace('-', '_')}"
BINNAME ?= "${BPN}"
LIBNAME ?= "lib${CRATE_NAME}-rs"
CRATE_TYPE ?= "dylib"
BIN_SRC ?= "${S}/src/main.rs"
LIB_SRC ?= "${S}/src/lib.rs"

get_overlap_externs () {
    externs=
    for dep in ${OVERLAP_DEPS}; do
        extern=$(ls ${STAGING_DIR_HOST}/${rustlibdir}/lib$dep-rs.{so,rlib} 2>/dev/null \
                    | awk '{print $1}');
        if [ -n "$extern" ]; then
            externs="$externs --extern $dep=$extern"
        else
            echo "$dep in depends but no such library found in ${rustlibdir}!" >&2
            exit 1
        fi
    done
    echo "$externs"
}

do_configure () {
}

oe_compile_rust_lib () {
    [ "${CRATE_TYPE}" == "dylib" ] && suffix=so || suffix=rlib
    rm -rf ${LIBNAME}.{rlib,so}
    local -a link_args
    if [ "${CRATE_TYPE}" == "dylib" ]; then
        link_args[0]="-C"
        link_args[1]="link-args=-Wl,-soname -Wl,${LIBNAME}.$suffix"
    fi
    oe_runrustc $(get_overlap_externs) \
        "${link_args[@]}" \
        ${LIB_SRC} \
        -o ${LIBNAME}.$suffix \
        --crate-name=${CRATE_NAME} --crate-type=${CRATE_TYPE} \
        "$@"
}
oe_compile_rust_lib[vardeps] += "get_overlap_externs"

oe_compile_rust_bin () {
    rm -rf ${BINNAME}
    oe_runrustc $(get_overlap_externs) ${BIN_SRC} -o ${BINNAME} "$@"
}
oe_compile_rust_bin[vardeps] += "get_overlap_externs"

oe_install_rust_lib () {
    for lib in $(ls ${LIBNAME}.{so,rlib} 2>/dev/null); do
        echo Installing $lib
        install -D -m 755 $lib ${D}/${rustlibdir}/$lib
    done
}

oe_install_rust_bin () {
    echo Installing ${BINNAME}
    install -D -m 755 ${BINNAME} ${D}/${bindir}/${BINNAME}
}

do_rust_bin_fixups() {
    for f in `find ${PKGD} -name '*.so*'`; do
        echo "Strip rust note: $f"
        ${OBJCOPY} -R .note.rustc $f $f
    done

    for f in `find ${PKGD}`; do
        file "$f" | grep -q ELF || continue
        readelf -d "$f" | grep RUNPATH | grep -q rustlib || continue
        echo "Set rpath:" "$f"
        patchelf --set-rpath '$ORIGIN:'${rustlibdir}:${rustlib} "$f"
    done
}

PACKAGE_PREPROCESS_FUNCS += "do_rust_bin_fixups"
