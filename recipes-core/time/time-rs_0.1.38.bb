DESCRIPTION = "Utilities for working with time-related functions in Rust"
HOMEPAGE = "https://github.com/rust-lang/time"
LICENSE = "MIT | Apache-2.0"
LIC_FILES_CHKSUM = "\
	file://LICENSE-MIT;md5=362255802eb5aa87810d12ddf3cfedb4 \
	file://LICENSE-APACHE;md5=1836efb2eb779966696f473ee8540542 \
"
DEPENDS = "libc-rs"

inherit rust-bin

SRC_URI = "git://github.com/rust-lang/time.git;protocol=https"
SRCREV = "d265b7cf9f50db74fbd0a01f8bec90ad7d239d48"

S = "${WORKDIR}/git"

do_compile () {
	oe_compile_rust_lib
}

do_install () {
	oe_install_rust_lib
}
