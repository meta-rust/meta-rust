HOMEPAGE = "https://github.com/rust-lang/regex"
LICENSE = "MIT | Apache-2.0"
LIC_FILES_CHKSUM = "\
	file://LICENSE-MIT;md5=362255802eb5aa87810d12ddf3cfedb4 \
	file://LICENSE-APACHE;md5=1836efb2eb779966696f473ee8540542 \
"

SRC_URI = "git://github.com/rust-lang/regex.git;protocol=https"
SRCREV = "c9e6781a6845478aa2d8ebc86972755f854fdbe0"
PV = "0.1.38"

inherit rust-bin

S = "${WORKDIR}/git"

do_compile () {
	oe_compile_rust_lib
}

do_install () {
	oe_install_rust_lib
}
