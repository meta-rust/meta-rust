SUMMARY = "All Rust libraries in this layer"
LICENSE = "MIT"

inherit packagegroup

RDEPENDS_${PN} = "\
    aho-corasick-rs \
    crypto-rs \
    dbus-rs \
    debug-builders-rs \
    env-logger-rs \
    getopts-rs \
    libc-rs \
    libudev-rs \
    libudev-sys-rs \
    log-rs \
    memchr-rs \
    rand-rs \
    regex-rs \
    regex-syntax-rs \
    rustc-serialize-rs \
    time-rs \
    unix-socket-rs \
    "

# Generating this list:
# From meta-rust/recipes-core
# find -name '*.bb' | sed 's#\./.*/##' | sed 's#\(_.*\)\?\.bb##' | sort | uniq
