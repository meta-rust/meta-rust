DESCRIPTION = "Unix domain socket bindings for Rust"
HOMEPAGE = "https://github.com/sfackler/rust-unix-socket"
LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://LICENSE;md5=bde86283c1fd74e84ebc3cf6dd7011d0"
DEPENDS = "libc-rs debug-builders-rs"

inherit rust-bin

SRC_URI = "git://github.com/sfackler/rust-unix-socket.git;protocol=https"
SRCREV = "d0f47ae888267a718072c3be5eed42ba1f637097"

S = "${WORKDIR}/git"

do_compile () {
	oe_compile_rust_lib
}

do_install () {
	oe_install_rust_lib
}
