DESCRIPTION = "Random number generators and other randomness functionality."
HOMEPAGE = "https://github.com/rust-lang/rand"
LICENSE = "MIT | Apache-2.0"
LIC_FILES_CHKSUM = "\
	file://LICENSE-MIT;md5=362255802eb5aa87810d12ddf3cfedb4 \
	file://LICENSE-APACHE;md5=1836efb2eb779966696f473ee8540542 \
"
DEPENDS = "libc-rs"

inherit rust-bin

SRC_URI = "git://github.com/rust-lang/rand.git;protocol=https"
SRCREV = "9d1c297ee98a1657f112b8ad653b81702864b357"

S = "${WORKDIR}/git"

do_compile () {
	oe_compile_rust_lib
}

do_install () {
	oe_install_rust_lib
}
