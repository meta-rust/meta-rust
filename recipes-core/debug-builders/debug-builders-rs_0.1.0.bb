DESCRIPTION = "A copy of libstd's debug builders for use before they stabilize"
HOMEPAGE = "https://github.com/sfackler/rust-debug-builders"
LICENSE = "MIT | Apache-2.0"
LIC_FILES_CHKSUM = "file://Cargo.toml;md5=97a131dc4ae910d242387f2c9d1a2ce8"

inherit rust-bin

SRC_URI = "git://github.com/sfackler/rust-debug-builders.git;protocol=https"
SRCREV = "c6943b72c7808ddaa151d08b824525cc7420cb9b"

S = "${WORKDIR}/git"

do_compile () {
	oe_compile_rust_lib
}

do_install () {
	oe_install_rust_lib
}
