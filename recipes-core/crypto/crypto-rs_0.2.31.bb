DESCRIPTION = "A (mostly) pure-Rust implementation of various common cryptographic algorithms."
HOMEPAGE = "https://github.com/DaGenix/rust-crypto/"
LICENSE = "MIT | Apache-2.0"
LIC_FILES_CHKSUM = "\
	file://LICENSE-MIT;md5=4311034aa04489226c1fc3f816dbfb5a \
	file://LICENSE-APACHE;md5=a02fef6dccf840318474c108a8281b77 \
"
DEPENDS = "\
	libc-rs \
	time-rs \
	rand-rs \
	rustc-serialize-rs \
"

inherit rust-bin

SRC_URI = "git://github.com/DaGenix/rust-crypto.git;protocol=https"
SRCREV = "5571cb41690b9cee12025192393ea7df0eddc21b"

S = "${WORKDIR}/git"

do_compile () {
	oe_compile_rust_lib
}

do_install () {
	oe_install_rust_lib
}
