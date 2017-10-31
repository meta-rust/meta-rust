# Specifics for Rust 1.21.0

## This is information on the rust-snapshot (binary) used to build our current release.
## snapshot info is taken from rust/src/stage0.txt
## TODO: find a way to add additional SRC_URIs based on the contents of an
##       earlier SRC_URI.
RS_VERSION = "1.20.0"

RUST_STD_SNAPSHOT = "rust-std-${RS_VERSION}-${RUST_BUILD_SYS}"
RUSTC_SNAPSHOT = "rustc-${RS_VERSION}-${RUST_BUILD_SYS}"
CARGO_VERSION = "0.21.0"
CARGO_SNAPSHOT = "cargo-${CARGO_VERSION}-${RUST_BUILD_SYS}"

SRC_URI += " \
	https://static.rust-lang.org/dist/${RUST_STD_SNAPSHOT}.tar.gz;name=rust-std-snapshot;subdir=rust-snapshot-components \
	https://static.rust-lang.org/dist/${RUSTC_SNAPSHOT}.tar.gz;name=rustc-snapshot;subdir=rust-snapshot-components \
	https://static.rust-lang.org/dist/${CARGO_SNAPSHOT}.tar.gz;name=cargo-snapshot;subdir=rust-snapshot-components \
	"

# These are x86_64-unknown-linux-gnu hashes, how can we add more?
SRC_URI[rustc-snapshot.md5sum] = "c6276176ec6061b61ae73617a64bceb0"
SRC_URI[rustc-snapshot.sha256sum] = "000e776431718a32b5d40c4aa6e09b3425f0b71dea8c95e718d29b8c0f5b35d3"
SRC_URI[rust-std-snapshot.md5sum] = "8c0f7355b66830517a51a2bd6f530327"
SRC_URI[rust-std-snapshot.sha256sum] = "a1b3e13b9d6f9aa713783145cb83070b1dabbe17349043b3528031d7712ca929"
SRC_URI[cargo-snapshot.md5sum] = "0e5389d2e38a14933dda77db8172cb1f"
SRC_URI[cargo-snapshot.sha256sum] = "caccf4ab039c806a9e6fdc7fe389cc88fb771e28e30d93c07a5c56ef845cdf57"
