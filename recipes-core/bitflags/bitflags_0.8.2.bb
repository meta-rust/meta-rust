DESCRIPTION = "A macro to generate structures which behave like bitflags."
HOMEPAGE = "https://github.com/rust-lang-nursery/bitflags"
LICENSE = "MIT | Apache-2.0"
LIC_FILES_CHKSUM = "\
	file://LICENSE-MIT;md5=362255802eb5aa87810d12ddf3cfedb4 \
	file://LICENSE-APACHE;md5=1836efb2eb779966696f473ee8540542 \
"

inherit rust-bin

SRC_URI = "git://github.com/rust-lang-nursery/bitflags.git;protocol=https;nobranch=1"
SRCREV = "e30da43cac0e52fc8d0007ce99a316ec6473033e"

S = "${WORKDIR}/git"

LIB_SRC = "${S}/src/lib.rs"
CRATE_TYPE = "rlib"
RUSTFLAGS += "-A pub_use_of_private_extern_crate"

do_compile () {
	oe_compile_rust_lib
}

do_install () {
	oe_install_rust_lib
}
