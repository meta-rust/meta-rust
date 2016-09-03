SUMMARY = "Rust standard libaries"
HOMEPAGE = "http://www.rust-lang.org"
SECTION = "devel"
LICENSE = "MIT | Apache-2.0"

LIC_FILES_CHKSUM ="file://COPYRIGHT;md5=43e1f1fb9c0ee3af66693d8c4fecafa8"
require rust-shared-source.inc

DEPENDS += "compiler-rt"

RUSTLIB_DEP = ""
inherit cargo_util

# Needed so cargo can find libbacktrace
RUSTFLAGS += "-L ${STAGING_LIBDIR}"

B = "${WORKDIR}/build"

do_compile () {
    cd ${S}/src/rustc/std_shim
    export CARGO_TARGET_DIR="${B}"
    export RUSTC_BOOTSTRAP_KEY="e8edd0fd"
    oe_cargo_fix_env
    oe_cargo_build
}

do_install () {
    mkdir -p ${D}${rustlibdir}
    cp ${B}/${TARGET_SYS}/release/deps/* ${D}${rustlibdir}
}
