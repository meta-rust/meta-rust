# Responseible for taking Yocto triples and converting it to Rust triples

def rust_base_triple(d, thing):
    '''
    Mangle bitbake's *_SYS into something that rust might support (see
    rust/mk/cfg/* for a list)

    Note that os is assumed to be some linux form
    '''

    arch = d.getVar('{}_ARCH'.format(thing), True)
    # All the Yocto targets are Linux and are 'unknown'
    vendor = "-unknown"
    os = d.getVar('{}_OS'.format(thing), True)
    libc = d.getVar('TCLIBC', True)

    # Prefix with a dash and convert glibc -> gnu
    if libc == "glibc":
        libc = "-gnu"
    elif libc == "musl":
        libc = "-musl"

    # Don't double up musl (only appears to be the case on aarch64)
    if os == "linux-musl":
        if libc != "-musl":
            bb.fatal("{}_OS was '{}' but TCLIBC was not 'musl'".format(thing, os))
        os = "linux"

    # This catches ARM targets and appends the necessary hard float bits
    if os == "linux-gnueabi" or os == "linux-musleabi":
        libc = bb.utils.contains('TUNE_FEATURES', 'callconvention-hard', 'hf', '', d)
    return arch + vendor + '-' + os + libc

# Naming explanation
# Yocto
# - BUILD_SYS - Yocto triple of the build environment
# - HOST_SYS - What we're building for in Yocto
# - TARGET_SYS - What we're building for in Yocto
#
# So when building '-native' packages BUILD_SYS == HOST_SYS == TARGET_SYS
# When building packages for the image HOST_SYS == TARGET_SYS
# This is a gross over simplification as there are other modes but
# currently this is all that's supported.
#
# Rust
# - TARGET - the system where the binary will run
# - HOST - the system where the binary is being built
#
# Rust additionally will use two additional cases:
# - undecorated (e.g. CC) - equivalent to TARGET
# - triple suffix (e.g. CC_x86_64_unknown_linux_gnu) - both
#   see: https://github.com/alexcrichton/gcc-rs
# The way that Rust's internal triples and Yocto triples are mapped together
# its likely best to not use the triple suffix due to potential confusion.

RUST_BUILD_SYS = "${@rust_base_triple(d, 'BUILD')}"
RUST_HOST_SYS = "${@rust_base_triple(d, 'HOST')}"
RUST_TARGET_SYS = "${@rust_base_triple(d, 'TARGET')}"
