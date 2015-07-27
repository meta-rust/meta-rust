DESCRIPTION = "getopts-like option parsing"
HOMEPAGE = "https://github.com/rust-lang/getopts"
LICENSE = "MIT | Apache-2.0"
LIC_FILES_CHKSUM = "\
	file://LICENSE-MIT;md5=362255802eb5aa87810d12ddf3cfedb4 \
	file://LICENSE-APACHE;md5=1836efb2eb779966696f473ee8540542 \
"
DEPENDS = "log-rs"

inherit rust-bin

SRC_URI = "git://github.com/rust-lang/getopts.git;protocol=https"
SRCREV = "a13c62b7d860b6d370129ebb972bf5e0373c5be7"

S = "${WORKDIR}/git"

do_compile () {
	oe_compile_rust_lib
}

do_install () {
	oe_install_rust_lib
}
