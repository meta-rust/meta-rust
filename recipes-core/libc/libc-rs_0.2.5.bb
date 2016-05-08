DESCRIPTION = "A Rust library with native bindings to the types and functions commonly found on various systems, including libc."
HOMEPAGE = "https://github.com/rust-lang/libc"
LICENSE = "MIT | Apache-2.0"
LIC_FILES_CHKSUM = "\
	file://LICENSE-MIT;md5=362255802eb5aa87810d12ddf3cfedb4 \
	file://LICENSE-APACHE;md5=1836efb2eb779966696f473ee8540542 \
"

inherit rust-bin

SRC_URI = "git://github.com/rust-lang/libc.git;protocol=https"
SRCREV = "f54b9c90ee68889181472d4d4a5dd9e43d0e5318"

S = "${WORKDIR}/git"

LIB_SRC = "${S}/src/lib.rs"

do_compile () {
	oe_compile_rust_lib --cfg feature='"cargo-build"'
}

do_install () {
	oe_install_rust_lib
}
