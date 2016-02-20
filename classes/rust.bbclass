RUSTC = "rustc"

# FIXME: --sysroot might be needed
RUSTC_ARCHFLAGS += "--target=${TARGET_SYS} -C rpath -C crate_hash=${BB_TASKHASH}"

def rust_base_dep(d):
    # Taken from meta/classes/base.bbclass `base_dep_prepend` and modified to
    # use rust instead of gcc
    deps = ""
    if not d.getVar('INHIBIT_DEFAULT_RUST_DEPS', True):
        if (d.getVar('HOST_SYS', True) != d.getVar('BUILD_SYS', True)):
            deps += " virtual/${TARGET_PREFIX}rust"
        else:
            deps += " rust-native"
    return deps

DEPENDS_append = " ${@rust_base_dep(d)}"

def rust_base_triple(d, thing):
    '''
    Mangle bitbake's *_SYS into something that rust might support (see
    rust/mk/cfg/* for a list)

    Note that os is assumed to be some linux form
    '''

    arch = d.getVar('{}_ARCH'.format(thing), True)
    vendor = d.getVar('{}_VENDOR'.format(thing), True)
    os = d.getVar('{}_OS'.format(thing), True)

    vendor = "-unknown"

    if arch.startswith("arm"):
        if os.endswith("gnueabi"):
            os += bb.utils.contains('TUNE_FEATURES', 'callconvention-hard', 'hf', '', d)
    elif arch.startswith("aarch64"):
        os = "linux-gnu"
    elif arch.startswith("x86_64"):
        os = "linux-gnu"
    elif arch.startswith("i586"):
        arch = "i686"
        os = "linux-gnu"
    return arch + vendor + '-' + os

RUST_BUILD_SYS = "${@rust_base_triple(d, 'BUILD')}"
RUST_HOST_SYS = "${@rust_base_triple(d, 'HOST')}"
RUST_TARGET_SYS = "${@rust_base_triple(d, 'TARGET')}"

# BUILD_LDFLAGS
# 	${STAGING_LIBDIR_NATIVE}
# 	${STAGING_BASE_LIBDIR_NATIVE}
# BUILDSDK_LDFLAGS
# 	${STAGING_LIBDIR}
# 	#{STAGING_DIR_HOST}
# TARGET_LDFLAGS ?????
#RUSTC_BUILD_LDFLAGS = "\
#	--sysroot ${STAGING_DIR_NATIVE} \
#	-L${STAGING_LIBDIR_NATIVE}	\
#	-L${STAGING_BASE_LIBDIR_NATIVE}	\
#"

RUST_PATH_NATIVE = "${STAGING_LIBDIR_NATIVE}:${STAGING_BASE_LIBDIR_NATIVE}"

## Note: the 'rustlib' element of this was a workaround rustc forgetting the
## libdir it was built with. It now remembers so this should be unneeded
#RUST_PATH_NATIVE .= ":${STAGING_LIBDIR_NATIVE}/${TARGET_SYS}/rustlib/${TARGET_SYS}/lib"

# FIXME: set based on whether we are native vs cross vs buildsdk, etc
#export RUST_PATH ??= "${RUST_PATH_NATIVE}"

## This is builtin to rustc with the value "$libdir/rust/targets"
# RUST_TARGET_PATH = "foo:bar"

oe_runrustc () {
	bbnote ${RUSTC} ${RUSTC_ARCHFLAGS} ${RUSTC_FLAGS} "$@"
	"${RUSTC}" ${RUSTC_ARCHFLAGS} ${RUSTC_FLAGS} "$@"
}

# XXX: for some reason bitbake sets BUILD_* & TARGET_* but uses the bare
# variables for HOST. Alias things to make it easier for us.
HOST_LDFLAGS  ?= "${LDFLAGS}"
HOST_CFLAGS   ?= "${CFLAGS}"
HOST_CXXFLAGS ?= "${CXXFLAGS}"
HOST_CPPFLAGS ?= "${CPPFLAGS}"

EXTRA_OECONF_remove = "--disable-static"
