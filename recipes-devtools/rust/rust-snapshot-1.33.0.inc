## This is information on the rust-snapshot (binary) used to build our current release.
## snapshot info is taken from rust/src/stage0.txt
## TODO: find a way to add additional SRC_URIs based on the contents of an
##       earlier SRC_URI.
RS_VERSION = "1.32.0"

RUST_STD_SNAPSHOT = "rust-std-${RS_VERSION}-${BUILD_ARCH}-unknown-linux-gnu"
RUSTC_SNAPSHOT = "rustc-${RS_VERSION}-${BUILD_ARCH}-unknown-linux-gnu"
CARGO_VERSION = "0.33.0"
CARGO_SNAPSHOT = "cargo-${CARGO_VERSION}-${BUILD_ARCH}-unknown-linux-gnu"

SRC_URI += " \
	https://static.rust-lang.org/dist/${RUST_STD_SNAPSHOT}.tar.gz;name=rust-std-snapshot-${BUILD_ARCH};subdir=rust-snapshot-components \
	https://static.rust-lang.org/dist/${RUSTC_SNAPSHOT}.tar.gz;name=rustc-snapshot-${BUILD_ARCH};subdir=rust-snapshot-components \
	https://static.rust-lang.org/dist/${CARGO_SNAPSHOT}.tar.gz;name=cargo-snapshot-${BUILD_ARCH};subdir=rust-snapshot-components \
	"

# TODO: Add hashes for other architecture toolchains as well. Make a script?
SRC_URI[rustc-snapshot-x86_64.md5sum] = "e8d74f3043fb0b566f6af0110a73af7f"
SRC_URI[rustc-snapshot-x86_64.sha256sum] = "75c31f32e19548c1608611d08b82b87560e02f15caac7b2663a8189a4609977c"
SRC_URI[rust-std-snapshot-x86_64.md5sum] = "5e644ee49ce9ce449824f9f0a4153409"
SRC_URI[rust-std-snapshot-x86_64.sha256sum] = "9f2705a3ed3217c13fd55569406c52f590030752f57520312e135223ae930caf"
SRC_URI[cargo-snapshot-x86_64.md5sum] = "13fbd6575ff9e5d865127bf0bff3b51d"
SRC_URI[cargo-snapshot-x86_64.sha256sum] = "9dd7f79a0ab882ed7c892731514a4aed6435f7bc8a20381a8346b471c8a14209"
