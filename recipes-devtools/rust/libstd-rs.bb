SUMMARY = "Rust standard libaries"
HOMEPAGE = "http://www.rust-lang.org"
SECTION = "devel"
LICENSE = "MIT | Apache-2.0"

LIC_FILES_CHKSUM ="file://COPYRIGHT;md5=43e1f1fb9c0ee3af66693d8c4fecafa8"
require rust-shared-source.inc

CARGO_INDEX_COMMIT = "6127fc24b0b6fe73fe4d339817fbf000b9a798a2"

SRC_URI += "\
	crate://crates.io/gcc/0.3.26 \
	crate-index://crates.io/${CARGO_INDEX_COMMIT} \
"

DEPENDS += "compiler-rt"

RUSTLIB_DEP = ""
inherit cargo

# Needed so cargo can find libbacktrace
RUSTFLAGS += "-L ${STAGING_LIBDIR}"

B = "${WORKDIR}/build"

do_compile_prepend () {
    cd ${S}/src/rustc/std_shim
    export CARGO_TARGET_DIR="${B}"
    export RUSTC_BOOTSTRAP_KEY="e8edd0fd"
}

do_install () {
    mkdir -p ${D}${rustlibdir}
    cp ${B}/${TARGET_SYS}/release/deps/* ${D}${rustlibdir}
}
