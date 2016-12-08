SUMMARY = "Rust standard libaries"
HOMEPAGE = "http://www.rust-lang.org"
SECTION = "devel"
LICENSE = "MIT | Apache-2.0"
LIC_FILES_CHKSUM ="file://COPYRIGHT;md5=43e1f1fb9c0ee3af66693d8c4fecafa8"

require rust-source-${PV}.inc

S = "${WORKDIR}/rustc-${PV}"

SRC_URI += "\
	crate://crates.io/gcc/0.3.27 \
"

DEPENDS += "compiler-rt (=${PV})"

RUSTLIB_DEP = ""
inherit cargo

# Needed so cargo can find libbacktrace
RUSTFLAGS += "-L ${STAGING_LIBDIR}"

S = "${WORKDIR}/rustc-${PV}"

do_compile_prepend () {
    cd ${S}/src/rustc/std_shim
    export CARGO_TARGET_DIR="${B}"
    export RUSTC_BOOTSTRAP_KEY="${RS_KEY}"
}

do_install () {
    mkdir -p ${D}${rustlibdir}
    cp ${B}/${TARGET_SYS}/release/deps/* ${D}${rustlibdir}
}
