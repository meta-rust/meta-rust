DESCRIPTION = "A collection of numeric types and traits for Rust, including bigint, complex, rational, range iterators, generic integers, and more!"
HOMEPAGE = "https://github.com/rust-num/num"
LICENSE = "MIT | Apache-2.0"
LIC_FILES_CHKSUM = "\
	file://LICENSE-MIT;md5=362255802eb5aa87810d12ddf3cfedb4 \
	file://LICENSE-APACHE;md5=1836efb2eb779966696f473ee8540542 \
"

inherit rust-bin

SRC_URI = "git://github.com/rust-num/num.git;protocol=https"
SRCREV = "d9f08cb148cc686ec407c1e42fbd4536cde6ac82"

S = "${WORKDIR}/git"

do_compile () {
	oe_compile_rust_lib
}

do_install () {
	oe_install_rust_lib
}
