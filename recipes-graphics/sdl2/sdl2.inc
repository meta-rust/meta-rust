DESCRIPTION = "SDL2 bindings for Rust"
HOMEPAGE = "https://github.com/AngryLawyer/rust-sdl2"
LICENSE = "MIT"
LIC_FILES_CHKSUM = "\
	file://LICENSE;md5=efab06594070f714e6e655a25c330fcd \
"

inherit rust-bin

SRC_URI = "git://github.com/AngryLawyer/rust-sdl2.git;protocol=https"
SRCREV = "ffdfe48bd90d8c141f1f8a6f38a88243ad78508f"

S = "${WORKDIR}/git"

do_compile () {
	oe_compile_rust_lib
}

do_install () {
	oe_install_rust_lib
}
