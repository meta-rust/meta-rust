require rust-source-${PV}.inc
require libstd-rs.inc

SRC_URI += "\
	crate://crates.io/gcc/0.3.27 \
"

# not necessary from Rust 1.15.x and newer as its built
# as a cargo crate with libstd
DEPENDS += "compiler-rt (=${PV})"

