DESCRIPTION = "A macro for declaring lazily evaluated statics in Rust."
HOMEPAGE = "https://github.com/rust-lang-nursery/lazy-static.rs"
LICENSE = "MIT"
LIC_FILES_CHKSUM = "\
	file://LICENSE;md5=5795ddb4df1d696d439b6667081cffc9 \
"

inherit rust-bin

SRC_URI = "git://github.com/rust-lang-nursery/lazy-static.rs.git;protocol=https"
SRCREV = "ffe65c818474f863945ca535c0e53f3b8b848ff7"

S = "${WORKDIR}/git"

LIB_SRC = "${S}/src/lib.rs"

do_compile () {
	oe_compile_rust_lib
}

do_install () {
	oe_install_rust_lib
}
