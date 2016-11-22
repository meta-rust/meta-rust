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

RUST_BUILD_SYS = "${@rust_base_triple(d, 'BUILD')}"
RUST_HOST_SYS = "${@rust_base_triple(d, 'HOST')}"
RUST_TARGET_SYS = "${@rust_base_triple(d, 'TARGET')}"
