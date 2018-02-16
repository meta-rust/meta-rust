# Specifics for Rust 1.24.0

## This is information on the rust-snapshot (binary) used to build our current release.
## snapshot info is taken from rust/src/stage0.txt
## TODO: find a way to add additional SRC_URIs based on the contents of an
##       earlier SRC_URI.
RS_VERSION = "1.23.0"

RUST_STD_SNAPSHOT = "rust-std-${RS_VERSION}-${RUST_BUILD_SYS}"
RUSTC_SNAPSHOT = "rustc-${RS_VERSION}-${RUST_BUILD_SYS}"
CARGO_VERSION = "0.24.0"
CARGO_SNAPSHOT = "cargo-${CARGO_VERSION}-${RUST_BUILD_SYS}"

SRC_URI += " \
	https://static.rust-lang.org/dist/${RUST_STD_SNAPSHOT}.tar.gz;name=rust-std-snapshot;subdir=rust-snapshot-components \
	https://static.rust-lang.org/dist/${RUSTC_SNAPSHOT}.tar.gz;name=rustc-snapshot;subdir=rust-snapshot-components \
	https://static.rust-lang.org/dist/${CARGO_SNAPSHOT}.tar.gz;name=cargo-snapshot;subdir=rust-snapshot-components \
	"

# These are x86_64-unknown-linux-gnu hashes, how can we add more?
SRC_URI[rustc-snapshot.md5sum] = "068fc6566772c4ce165cc547151f514c"
SRC_URI[rustc-snapshot.sha256sum] = "27b124fd0d94c082978ff81e45f7b7c37e91d64714587829bf828d64d76524ee"
SRC_URI[rust-std-snapshot.md5sum] = "f9f89caf41e3f9c092118272ceb5bf6b"
SRC_URI[rust-std-snapshot.sha256sum] = "83c7351bdc4326caf785c208cff86682825dad4a89ccee705fa05f55ce7bd25b"
SRC_URI[cargo-snapshot.md5sum] = "830041cfc8627d3f7187954993449cf9"
SRC_URI[cargo-snapshot.sha256sum] = "ff8a454104aba20426ea898ed7515ec5da7de07d11733cdda17462455beb76e8"
