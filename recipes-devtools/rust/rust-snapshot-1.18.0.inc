# Specifics for Rust 1.18.0

## This is information on the rust-snapshot (binary) used to build our current release.
## snapshot info is taken from rust/src/stage0.txt
## TODO: find a way to add additional SRC_URIs based on the contents of an
##       earlier SRC_URI.
RS_VERSION = "1.17.0"

RUST_STD_SNAPSHOT = "rust-std-${RS_VERSION}-${RUST_BUILD_SYS}"
RUSTC_SNAPSHOT = "rustc-${RS_VERSION}-${RUST_BUILD_SYS}"
CARGO_SNAPSHOT = "cargo-0.18.0-${RUST_BUILD_SYS}"

SRC_URI += " \
	https://static.rust-lang.org/dist/${RUST_STD_SNAPSHOT}.tar.gz;name=rust-std-snapshot;subdir=rust-snapshot-components \
	https://static.rust-lang.org/dist/${RUSTC_SNAPSHOT}.tar.gz;name=rustc-snapshot;subdir=rust-snapshot-components \
	https://static.rust-lang.org/dist/${CARGO_SNAPSHOT}.tar.gz;name=cargo-snapshot;subdir=rust-snapshot-components \
"

# These are x86_64-unknown-linux-gnu hashes, how can we add more?
SRC_URI[rustc-snapshot.md5sum] = "894b45835cf28d6ddb3f04addc937dcc"
SRC_URI[rustc-snapshot.sha256sum] = "3eebd92512040baf3c0974c3ce61859646d8cf422cc515d724d857577da0dbd5"
SRC_URI[rust-std-snapshot.md5sum] = "5c484d5c1ddd633c4473f1edc607266b"
SRC_URI[rust-std-snapshot.sha256sum] = "2902bb0da78208f441f1d983aeafcad01ea653d2e062a8192892868e2b41130d"
SRC_URI[cargo-snapshot.md5sum] = "d2cbab6378c1f60b483efa0f076a8f81"
SRC_URI[cargo-snapshot.sha256sum] = "3601e95c968850230b137b849ff08a507e50d77ab584c779143a100f1843d8dd"
