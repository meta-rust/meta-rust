DESCRIPTION = "FFI bindings to libudev"
HOMEPAGE = "https://github.com/dcuddeback/libudev-sys"
LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://LICENSE;md5=bbd2acd29c4ba5d4591b03e2757c04a3"

DEPENDS += "libudev-sys-rs"
DEPENDS += "libc-rs"

inherit rust-bin

SRC_URI = "git://github.com/dcuddeback/libudev-rs.git;protocol=https"
SRCREV = "3da791245f206d0cf5a856531c574b8646b0f059"

S = "${WORKDIR}/git"

do_compile () {
	oe_compile_rust_lib
}

do_install () {
	oe_install_rust_lib
}
