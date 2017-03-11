SUMMARY = "Rust standard libaries"
HOMEPAGE = "http://www.rust-lang.org"
SECTION = "devel"
LICENSE = "MIT | Apache-2.0"
LIC_FILES_CHKSUM ="file://COPYRIGHT;md5=43e1f1fb9c0ee3af66693d8c4fecafa8"

RUSTLIB_DEP = ""
inherit cargo

# Needed so cargo can find libbacktrace
RUSTFLAGS += "-L ${STAGING_LIBDIR}"

do_compile_prepend () {
    cd ${S}/src/rustc/std_shim
    export CARGO_TARGET_DIR="${B}"
    # For Rust 1.12.1 and lower
    export RUSTC_BOOTSTRAP_KEY="${RS_KEY}"
    # For Rust 1.13.0 and newer
    export RUSTC_BOOTSTRAP="1"
}

do_install () {
    mkdir -p ${D}${rustlibdir}
    cp ${B}/${TARGET_SYS}/release/deps/* ${D}${rustlibdir}
}
