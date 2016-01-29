DESCRIPTION = "FFI bindings to libudev"
HOMEPAGE = "https://github.com/dcuddeback/libudev-sys"
LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://LICENSE;md5=bbd2acd29c4ba5d4591b03e2757c04a3"
DEPENDS = "libc-rs udev"

inherit rust-bin

SRC_URI = "git://github.com/dcuddeback/libudev-sys.git;protocol=https"
SRCREV = "c49163f87d4d109ec21bcf8f8c51db560ed31b22"

S = "${WORKDIR}/git"

RUSTC_FLAGS += "-ludev"

do_compile () {
	oe_compile_rust_lib
}

do_install () {
	oe_install_rust_lib
}
