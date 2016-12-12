DESCRIPTION = "Generic serialization/deserialization support"
HOMEPAGE = "https://github.com/rust-lang/rustc-serialize"
LICENSE = "MIT | Apache-2.0"
LIC_FILES_CHKSUM = "\
	file://LICENSE-MIT;md5=362255802eb5aa87810d12ddf3cfedb4 \
	file://LICENSE-APACHE;md5=1836efb2eb779966696f473ee8540542 \
"

inherit rust-bin

SRC_URI = "git://github.com/rust-lang/rustc-serialize.git;protocol=https"
SRCREV = "64b38a1f31a9af6eabf2894437aa5ccc3e457e68"

S = "${WORKDIR}/git"

do_compile () {
	oe_compile_rust_lib
}

do_install () {
	oe_install_rust_lib
}
