DESCRIPTION = "Safe interface to memchr"
HOMEPAGE = "https://github.com/BurntSushi/rust-memchr"
LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://LICENSE-MIT;md5=8d0d0aa488af0ab9aafa3b85a7fc8e12"
DEPENDS = "libc-rs"

inherit rust-bin

SRC_URI = "git://github.com/BurntSushi/rust-memchr.git;protocol=https"
SRCREV = "a91e63378bf6f4bba5c7d88f4fe98efdcb432c99"

S = "${WORKDIR}/git"

# This module is tiny. One wrapper function only.
CRATE_TYPE = "rlib"

do_compile () {
	oe_compile_rust_lib
}

do_install () {
	oe_install_rust_lib
}
