DESCRIPTION = "Utilities for working with time-related functions in Rust"
HOMEPAGE = "https://github.com/rust-lang-deprecated/time"
LICENSE = "MIT | Apache-2.0"
LIC_FILES_CHKSUM = "\
	file://LICENSE-MIT;md5=362255802eb5aa87810d12ddf3cfedb4 \
	file://LICENSE-APACHE;md5=1836efb2eb779966696f473ee8540542 \
"
DEPENDS = "libc-rs"

inherit rust-bin

SRC_URI = "https://github.com/rust-lang-deprecated/time/archive/0.1.35.tar.gz"
SRC_URI[md5sum] = "894c058c9510214ddf07c118fc627694"
SRC_URI[sha256sum] = "6b5aed1f9e5660c3e71db96189dcb1f7f0b8604880dde8412a0c02aa7bd08bad"

S = "${WORKDIR}/time-${PV}"

do_compile () {
	oe_compile_rust_lib
}

do_install () {
	oe_install_rust_lib
}
