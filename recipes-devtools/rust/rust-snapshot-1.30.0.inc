# Specifics for Rust 1.30.0

## This is information on the rust-snapshot (binary) used to build our current release.
## snapshot info is taken from rust/src/stage0.txt
## TODO: find a way to add additional SRC_URIs based on the contents of an
##       earlier SRC_URI.
RS_VERSION = "1.29.0"

RUST_STD_SNAPSHOT = "rust-std-${RS_VERSION}-${BUILD_ARCH}-unknown-linux-gnu"
RUSTC_SNAPSHOT = "rustc-${RS_VERSION}-${BUILD_ARCH}-unknown-linux-gnu"
CARGO_VERSION = "0.30.0"
CARGO_SNAPSHOT = "cargo-${CARGO_VERSION}-${BUILD_ARCH}-unknown-linux-gnu"

SRC_URI += " \
	https://static.rust-lang.org/dist/${RUST_STD_SNAPSHOT}.tar.gz;name=rust-std-snapshot-${BUILD_ARCH};subdir=rust-snapshot-components \
	https://static.rust-lang.org/dist/${RUSTC_SNAPSHOT}.tar.gz;name=rustc-snapshot-${BUILD_ARCH};subdir=rust-snapshot-components \
	https://static.rust-lang.org/dist/${CARGO_SNAPSHOT}.tar.gz;name=cargo-snapshot-${BUILD_ARCH};subdir=rust-snapshot-components \
	"

# TODO: Add hashes for other architecture toolchains as well. Make a script?
SRC_URI[rustc-snapshot-x86_64.md5sum] = "755b21e83a09f5333c31e8fe86ada0f1"
SRC_URI[rustc-snapshot-x86_64.sha256sum] = "229c51d51efc239e6eb9b428795bb7f57309f11287705dcba4877d5e220102a0"
SRC_URI[rust-std-snapshot-x86_64.md5sum] = "6ad96aa7c8a84a34e5c291316c4b9285"
SRC_URI[rust-std-snapshot-x86_64.sha256sum] = "0bed2fcba596e1af6f56ed3f5d481b89b28a4ac26aea07128c6630c00c6a136b"
SRC_URI[cargo-snapshot-x86_64.md5sum] = "79b62c75b11ef480163276be189fdac5"
SRC_URI[cargo-snapshot-x86_64.sha256sum] = "32f210fd3142fda7825a06e95d1aa4b54035c2da435d8cf0dd03fad410c8002f"
