DESCRIPTION = "Generic serialization/deserialization support"
HOMEPAGE = "https://github.com/rust-lang/rustc-serialize"
LICENSE = "MIT | Apache-2.0"
LIC_FILES_CHKSUM = "\
	file://LICENSE-MIT;md5=362255802eb5aa87810d12ddf3cfedb4 \
	file://LICENSE-APACHE;md5=1836efb2eb779966696f473ee8540542 \
"

inherit rust-bin

SRC_URI = "git://github.com/rust-lang/rustc-serialize.git;protocol=https"
SRCREV = "376f43a4b94dbe411bd9534ab83f02fbcb5a3b04"

S = "${WORKDIR}/git"

do_compile () {
	oe_compile_rust_lib
}

do_install () {
	oe_install_rust_lib
}
