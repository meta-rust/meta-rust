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
SRCREV = "32b212b877b836dbfdc97af5674d91672e70ecbd"

S = "${WORKDIR}/git"

do_compile () {
	rm -rf time_helpers.o libtimehelpers.a
	${CC} ${S}/src/time_helpers.c -fPIC -c -o time_helpers.o
	${AR} rcs libtime_helpers.a time_helpers.o
	oe_compile_rust_lib -L native=$PWD -l static=time_helpers
}

do_install () {
	oe_install_rust_lib
}
