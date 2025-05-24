require rust-source-${PV}.inc
require libstd-rs.inc

LIC_FILES_CHKSUM = "file://../../COPYRIGHT;md5=11a3899825f4376896e438c8c753f8dc"

# libstd moved from src/libstd to library/std in 1.47+
S = "${RUSTSRC}/library/std"

# ref: https://github.com/rust-lang/rust/issues/133857
RUSTFLAGS += "-Zforce-unstable-if-unmarked"
