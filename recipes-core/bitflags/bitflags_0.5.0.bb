DESCRIPTION = "A macro to generate structures which behave like bitflags."
HOMEPAGE = "https://github.com/rust-lang-nursery/bitflags"
LICENSE = "MIT | Apache-2.0"
LIC_FILES_CHKSUM = "\
	file://LICENSE-MIT;md5=362255802eb5aa87810d12ddf3cfedb4 \
	file://LICENSE-APACHE;md5=1836efb2eb779966696f473ee8540542 \
"

inherit rust-bin

SRC_URI = "git://github.com/rust-lang-nursery/bitflags.git;protocol=https"
SRCREV = "41aa413a7c30d70b93b44ab5447276c381ef249e"

S = "${WORKDIR}/git"

LIB_SRC = "${S}/src/lib.rs"

do_compile () {
	oe_compile_rust_lib
}

do_install () {
	oe_install_rust_lib
}
