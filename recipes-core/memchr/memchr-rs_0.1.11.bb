DESCRIPTION = "Safe interface to memchr"
HOMEPAGE = "https://github.com/BurntSushi/rust-memchr"
LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://LICENSE-MIT;md5=8d0d0aa488af0ab9aafa3b85a7fc8e12"
DEPENDS = "libc-rs"

inherit rust-bin

SRC_URI = "https://github.com/BurntSushi/rust-memchr/archive/${PV}.tar.gz"
SRC_URI[md5sum] = "398b9b640981d6d5b276126f82dc2faf"
SRC_URI[sha256sum] = "2c138b8a2b86e3c570d854049893d6496c810f7682a0f81e033fdeb9a4b941cf"

S = "${WORKDIR}/rust-memchr-${PV}"

do_compile () {
	oe_compile_rust_lib
}

do_install () {
	oe_install_rust_lib
}
