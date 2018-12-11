# Specifics for Rust 1.31.0

## This is information on the rust-snapshot (binary) used to build our current release.
## snapshot info is taken from rust/src/stage0.txt
## TODO: find a way to add additional SRC_URIs based on the contents of an
##       earlier SRC_URI.
RS_VERSION = "1.30.0"

RUST_STD_SNAPSHOT = "rust-std-${RS_VERSION}-${BUILD_ARCH}-unknown-linux-gnu"
RUSTC_SNAPSHOT = "rustc-${RS_VERSION}-${BUILD_ARCH}-unknown-linux-gnu"
CARGO_VERSION = "0.31.0"
CARGO_SNAPSHOT = "cargo-${CARGO_VERSION}-${BUILD_ARCH}-unknown-linux-gnu"

SRC_URI += " \
	https://static.rust-lang.org/dist/${RUST_STD_SNAPSHOT}.tar.gz;name=rust-std-snapshot-${BUILD_ARCH};subdir=rust-snapshot-components \
	https://static.rust-lang.org/dist/${RUSTC_SNAPSHOT}.tar.gz;name=rustc-snapshot-${BUILD_ARCH};subdir=rust-snapshot-components \
	https://static.rust-lang.org/dist/${CARGO_SNAPSHOT}.tar.gz;name=cargo-snapshot-${BUILD_ARCH};subdir=rust-snapshot-components \
	"

# TODO: Add hashes for other architecture toolchains as well. Make a script?
SRC_URI[rustc-snapshot-x86_64.md5sum] = "262fe55e3261ecf601d3a434afdc6832"
SRC_URI[rustc-snapshot-x86_64.sha256sum] = "cc45058e9963d33ca28220e752d9e360b7e05f17e34284f5f8197738c3a88444"
SRC_URI[rust-std-snapshot-x86_64.md5sum] = "0e8831c2b916b2391734a3f46dd586b0"
SRC_URI[rust-std-snapshot-x86_64.sha256sum] = "8514eedc0ed99ab75c61be3137c3e57c4115063ddc07aec842f687ebfc7ceda3"
SRC_URI[cargo-snapshot-x86_64.md5sum] = "bad665c07e73a3f3cfa7ec3b209737fc"
SRC_URI[cargo-snapshot-x86_64.sha256sum] = "bfbabba9a2c1717fe1ce68469ce2de7b4b94e44e6a165d50b77de7bf7515bdb6"
