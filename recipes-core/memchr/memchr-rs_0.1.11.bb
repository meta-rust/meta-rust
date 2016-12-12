DESCRIPTION = "Safe interface to memchr"
HOMEPAGE = "https://github.com/BurntSushi/rust-memchr"
LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://LICENSE-MIT;md5=8d0d0aa488af0ab9aafa3b85a7fc8e12"
DEPENDS = "libc-rs"

inherit rust-bin

SRC_URI = "git://github.com/BurntSushi/rust-memchr.git;protocol=https"
SRCREV = "4f9a13f95e6e00f2847c093c56b41b9c1d58d3c4"

S = "${WORKDIR}/git"

do_compile () {
	oe_compile_rust_lib
}

do_install () {
	oe_install_rust_lib
}
