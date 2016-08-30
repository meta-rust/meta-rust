require sdl2.inc

DEPENDS += "\
	libc-rs \
	lazy-static \
	bitflags \
	rand-rs \
	num \
	sdl2-sys \
	"

LIB_SRC = "${S}/src/sdl2/lib.rs"
