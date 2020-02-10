## This is information on the rust-snapshot (binary) used to build our current release.
## snapshot info is taken from rust/src/stage0.txt
## TODO: find a way to add additional SRC_URIs based on the contents of an
##       earlier SRC_URI.
RS_VERSION = "1.40.0"

RUSTC_SNAPSHOT = "rustc-${RS_VERSION}-${BUILD_ARCH}-unknown-linux-gnu"
RUST_STD_SNAPSHOT = "rust-std-${RS_VERSION}-${BUILD_ARCH}-unknown-linux-gnu"
CARGO_VERSION = "0.41.0"
CARGO_SNAPSHOT = "cargo-${CARGO_VERSION}-${BUILD_ARCH}-unknown-linux-gnu"

SRC_URI += " \
	https://static.rust-lang.org/dist/${RUSTC_SNAPSHOT}.tar.xz;name=rustc-snapshot-${BUILD_ARCH};subdir=rust-snapshot-components \
	https://static.rust-lang.org/dist/${RUST_STD_SNAPSHOT}.tar.xz;name=rust-std-snapshot-${BUILD_ARCH};subdir=rust-snapshot-components \
	https://static.rust-lang.org/dist/${CARGO_SNAPSHOT}.tar.xz;name=cargo-snapshot-${BUILD_ARCH};subdir=rust-snapshot-components \
	"

# TODO: Add hashes for other architecture toolchains as well. Make a script?
SRC_URI[rustc-snapshot-x86_64.md5sum] = "5c62bca8ce4beb9b15e42fb8b9690935"
SRC_URI[rustc-snapshot-x86_64.sha256sum] = "b1c00618b7a98156e88b14682508a503284f85748eab23de749a20dcc8847111"
SRC_URI[rust-std-snapshot-x86_64.md5sum] = "2f926b4eda6449079665045becff623d"
SRC_URI[rust-std-snapshot-x86_64.sha256sum] = "5a0b14a51f51b0194f70a2023749d9cb49c3b2e11f0d4c8232960b91fad336ac"
SRC_URI[cargo-snapshot-x86_64.md5sum] = "8ea9f8b849d44abf2abf9180f90cc4b6"
SRC_URI[cargo-snapshot-x86_64.sha256sum] = "9b6ae643fa240c5ecbc1dc390f4020b6a683f25bac6f7437ebd4b9d32a8d0b6c"
