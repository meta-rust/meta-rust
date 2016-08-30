require sdl2.inc

DEPENDS += "\
	libc-rs \
	libsdl2 \
	"

LIB_SRC = "${S}/sdl2-sys/src/lib.rs"
