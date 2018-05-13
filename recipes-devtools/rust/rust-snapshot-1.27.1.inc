# Specifics for Rust 1.27.1

## This is information on the rust-snapshot (binary) used to build our current release.
## snapshot info is taken from rust/src/stage0.txt
## TODO: find a way to add additional SRC_URIs based on the contents of an
##       earlier SRC_URI.
RS_VERSION = "1.26.0"

RUST_STD_SNAPSHOT = "rust-std-${RS_VERSION}-${BUILD_ARCH}-unknown-linux-gnu"
RUSTC_SNAPSHOT = "rustc-${RS_VERSION}-${BUILD_ARCH}-unknown-linux-gnu"
CARGO_VERSION = "0.27.0"
CARGO_SNAPSHOT = "cargo-${CARGO_VERSION}-${BUILD_ARCH}-unknown-linux-gnu"

SRC_URI += " \
	https://static.rust-lang.org/dist/${RUST_STD_SNAPSHOT}.tar.gz;name=rust-std-snapshot-${BUILD_ARCH};subdir=rust-snapshot-components \
	https://static.rust-lang.org/dist/${RUSTC_SNAPSHOT}.tar.gz;name=rustc-snapshot-${BUILD_ARCH};subdir=rust-snapshot-components \
	https://static.rust-lang.org/dist/${CARGO_SNAPSHOT}.tar.gz;name=cargo-snapshot-${BUILD_ARCH};subdir=rust-snapshot-components \
	"

# TODO: Add hashes for other architecture toolchains as well. Make a script?
SRC_URI[rustc-snapshot-x86_64.md5sum] = "939631f19dd9ca5ae8493dc8ec2d3131"
SRC_URI[rustc-snapshot-x86_64.sha256sum] = "7ca9a30010602aaf2244c376a3cc5baa89429d54da17b8ba1cb0cdfdc846cc61"
SRC_URI[rust-std-snapshot-x86_64.md5sum] = "643460e582de498eea53ec1e93aeabab"
SRC_URI[rust-std-snapshot-x86_64.sha256sum] = "e27cb5c21541a500c8df919e15c8d3b002456ebbe573122e7b058cf5b4c3c13a"
SRC_URI[cargo-snapshot-x86_64.md5sum] = "ca366ba1e97ffc02b72dc74859db35e2"
SRC_URI[cargo-snapshot-x86_64.sha256sum] = "8c17710252513d8130141f2c12b4efeef67f0def252b94b246fe326a9a75043b"
