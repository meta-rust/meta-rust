# Specifics for Rust 1.26.2

## This is information on the rust-snapshot (binary) used to build our current release.
## snapshot info is taken from rust/src/stage0.txt
## TODO: find a way to add additional SRC_URIs based on the contents of an
##       earlier SRC_URI.
RS_VERSION = "1.25.0"

RUST_STD_SNAPSHOT = "rust-std-${RS_VERSION}-${BUILD_ARCH}-unknown-linux-gnu"
RUSTC_SNAPSHOT = "rustc-${RS_VERSION}-${BUILD_ARCH}-unknown-linux-gnu"
CARGO_VERSION = "0.26.0"
CARGO_SNAPSHOT = "cargo-${CARGO_VERSION}-${BUILD_ARCH}-unknown-linux-gnu"

SRC_URI += " \
	https://static.rust-lang.org/dist/${RUST_STD_SNAPSHOT}.tar.gz;name=rust-std-snapshot-${BUILD_ARCH};subdir=rust-snapshot-components \
	https://static.rust-lang.org/dist/${RUSTC_SNAPSHOT}.tar.gz;name=rustc-snapshot-${BUILD_ARCH};subdir=rust-snapshot-components \
	https://static.rust-lang.org/dist/${CARGO_SNAPSHOT}.tar.gz;name=cargo-snapshot-${BUILD_ARCH};subdir=rust-snapshot-components \
	"

# TODO: Add hashes for other architecture toolchains as well. Make a script?
SRC_URI[rustc-snapshot-x86_64.md5sum] = "6e9c8ae2946cf6626ad6511c7a1d6c2a"
SRC_URI[rustc-snapshot-x86_64.sha256sum] = "f8f4ae2f4b76416bfa90758267df4280dd078235dfba92dac0431595493443be"
SRC_URI[rust-std-snapshot-x86_64.md5sum] = "37e9f9193413caba47134af3306328c5"
SRC_URI[rust-std-snapshot-x86_64.sha256sum] = "a3258308e3a9fe364d63b5d782efb285ab410bdfc01d168c119122ddbc9a02e2"
SRC_URI[cargo-snapshot-x86_64.md5sum] = "b0de62d86f0ba71078471d09916873c6"
SRC_URI[cargo-snapshot-x86_64.sha256sum] = "9ba227f2364f618dc9415dacf3a5dce17458e1cb9f6d4fe860416cb68db894e4"
