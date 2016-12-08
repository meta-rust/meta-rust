DESCRIPTION = "SDL2 bindings for Rust"
HOMEPAGE = "https://github.com/AngryLawyer/rust-sdl2"
LICENSE = "MIT"
LIC_FILES_CHKSUM = "\
	file://LICENSE;md5=d8786ddfe98d69e641491528dd88fa55 \
"

DEPENDS += "\
	bitflags \
	sdl2-sys \
	sdl2-rs \
	libsdl2-ttf \
	"

inherit rust-bin

LIB_SRC = "${S}/src/sdl2_ttf/lib.rs"

SRC_URI = "git://github.com/andelf/rust-sdl2_ttf.git;protocol=https"
SRCREV = "203a550a804aed79e6ad6c1fcc0ed9e31e9ca2f4"

S = "${WORKDIR}/git"

do_compile () {
	oe_compile_rust_lib
}

do_install () {
	oe_install_rust_lib
}
