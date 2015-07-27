DESCRIPTION = "Fast multiple substring searching with finite state machines."
HOMEPAGE = "https://github.com/BurntSushi/aho-corasick"
LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://LICENSE-MIT;md5=8d0d0aa488af0ab9aafa3b85a7fc8e12"
DEPENDS = "memchr-rs"

inherit rust-bin

SRC_URI = "git://github.com/BurntSushi/aho-corasick.git;protocol=https"
SRCREV = "e1bca33dcc060d587e802320a79cbb035f37f8fa"

S = "${WORKDIR}/git"

do_compile () {
	oe_compile_rust_lib
}

do_install () {
	oe_install_rust_lib
}
