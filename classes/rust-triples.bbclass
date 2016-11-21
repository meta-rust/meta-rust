# Responseible for taking Yocto triples and converting it to Rust triples

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
