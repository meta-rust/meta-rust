# Specifics for Rust 1.24.0

## This is information on the rust-snapshot (binary) used to build our current release.
## snapshot info is taken from rust/src/stage0.txt
## TODO: find a way to add additional SRC_URIs based on the contents of an
##       earlier SRC_URI.
RS_VERSION = "${PV}"

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
SRC_URI[rustc-snapshot.md5sum] = "218f955f0b3ba90b97845619609828c0"
SRC_URI[rustc-snapshot.sha256sum] = "61f4853ba83fbe574663973499c3f32009eeccc2f1c83e10c3eb78549aebdfdb"
SRC_URI[rust-std-snapshot.md5sum] = "ad8b5a2e844eaa48760d53278de20da6"
SRC_URI[rust-std-snapshot.sha256sum] = "bf421f0f3af569b89dcb8f6b1508bb39be9d5c29bd47282fd9630709c65b71f1"
SRC_URI[cargo-snapshot.md5sum] = "830041cfc8627d3f7187954993449cf9"
SRC_URI[cargo-snapshot.sha256sum] = "ff8a454104aba20426ea898ed7515ec5da7de07d11733cdda17462455beb76e8"
