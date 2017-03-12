# Specifics for Rust 1.15.1

## This is information on the rust-snapshot (binary) used to build our current release.
## snapshot info is taken from rust/src/stage0.txt
## TODO: find a way to add additional SRC_URIs based on the contents of an
##       earlier SRC_URI.
RS_VERSION = "1.14.0"

RUST_STD_SNAPSHOT = "rust-std-${RS_VERSION}-${RUST_BUILD_SYS}"
RUSTC_SNAPSHOT = "rustc-${RS_VERSION}-${RUST_BUILD_SYS}"
CARGO_REV = "fbeea902d2c9a5be6d99cc35681565d8f7832592"
CARGO_SNAPSHOT = "cargo-nightly-${RUST_BUILD_SYS}"

SRC_URI += " \
	https://static.rust-lang.org/dist/${RUST_STD_SNAPSHOT}.tar.gz;name=rust-std-snapshot;subdir=rust-snapshot-components \
	https://static.rust-lang.org/dist/${RUSTC_SNAPSHOT}.tar.gz;name=rustc-snapshot;subdir=rust-snapshot-components \
"

# Downloaded cargo tarballs must be named differently to distinguish between versions.
SRC_URI += " \
	https://s3.amazonaws.com/rust-lang-ci/cargo-builds/${CARGO_REV}/${CARGO_SNAPSHOT}.tar.gz;name=cargo-snapshot;subdir=rust-snapshot-components;downloadfilename=${CARGO_SNAPSHOT}-${CARGO_REV}.tar.gz \
"

# These are x86_64-unknown-linux-gnu hashes, how can we add more?
SRC_URI[rustc-snapshot.md5sum] = "f178d9d6aad0f87c451f4b2f93170633"
SRC_URI[rustc-snapshot.sha256sum] = "0eeec4211aa872f24c220200a0c2b095bbfc9c0f737c1c5df2555967c8f36787"
SRC_URI[rust-std-snapshot.md5sum] = "518e492fc3d50d8c678056eb788bd0e7"
SRC_URI[rust-std-snapshot.sha256sum] = "3a609bfe9572c742d71199faad578ee76abe9067cd8df698bda6e3ef5caf6ec4"
SRC_URI[cargo-snapshot.md5sum] = "59bc24d15c393de364dadb3f4e3c9a5a"
SRC_URI[cargo-snapshot.sha256sum] = "0e052514ee88f236153a0d6c6f38f66d691eb4cf1ac09e6040d96e5101d57800"
