DESCRIPTION = "FFI bindings to libudev"
HOMEPAGE = "https://github.com/dcuddeback/libudev-sys"
LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://LICENSE;md5=bbd2acd29c4ba5d4591b03e2757c04a3"
DEPENDS = "libudev-sys-rs"

inherit rust-bin

SRC_URI = "git://github.com/dcuddeback/libudev-rs.git;protocol=https"
SRCREV = "d55763c626790e2e8724947503238731843a969a"

S = "${WORKDIR}/git"

do_compile () {
	oe_compile_rust_lib
}

do_install () {
	oe_install_rust_lib
}
