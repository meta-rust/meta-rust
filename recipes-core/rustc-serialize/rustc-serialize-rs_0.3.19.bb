DESCRIPTION = "Generic serialization/deserialization support"
HOMEPAGE = "https://github.com/rust-lang/rustc-serialize"
LICENSE = "MIT | Apache-2.0"
LIC_FILES_CHKSUM = "\
	file://LICENSE-MIT;md5=362255802eb5aa87810d12ddf3cfedb4 \
	file://LICENSE-APACHE;md5=1836efb2eb779966696f473ee8540542 \
"

inherit rust-bin

SRC_URI = "https://github.com/rust-lang-nursery/rustc-serialize/archive/0.3.19.tar.gz"
SRC_URI[md5sum] = "575425ea16d171da8f799a5eb170b4c1"
SRC_URI[sha256sum] = "9e96ba43f2722bf4e79a38acad35d5f1fe19a6f3d2b5316f90b2fb2b87ddbecd"

S = "${WORKDIR}/rustc-serialize-${PV}"

do_compile () {
	oe_compile_rust_lib
}

do_install () {
	oe_install_rust_lib
}
