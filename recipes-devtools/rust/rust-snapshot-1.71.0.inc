## This is information on the rust-snapshot (binary) used to build our current release.
## snapshot info is taken from rust/src/stage0.json
## Rust is self-hosting and bootstraps itself with a pre-built previous version of itself.
## The exact (previous) version that has been used is specified in the source tarball.
## The version is replicated here.
## TODO: find a way to add additional SRC_URIs based on the contents of an
##       earlier SRC_URI.

SNAPSHOT_VERSION = "1.70.0"

# TODO: Add hashes for other architecture toolchains as well. Make a script?
SRC_URI[rust-std-snapshot-x86_64.sha256sum] = "0c0129717da1e27ccf2c56da950d2fe56973f71beec9e80ae6904b282d2f0ee9"
SRC_URI[rustc-snapshot-x86_64.sha256sum] = "7d891d3e9bc4f1151545c83cbe3bc6af9ed234388c45ca2e19641262f48615e2"
SRC_URI[cargo-snapshot-x86_64.sha256sum] = "650e7a890a52869cd14e2305652bff775aec7fc2cf47fc62cf4a89ff07242333"

SRC_URI[rust-std-snapshot-aarch64.sha256sum] = "966e85187b6b76dc520b23aadc886c5fe54b209a21c68f959ff00ef8542b7f9f"
SRC_URI[rustc-snapshot-aarch64.sha256sum] = "71698cf444eef74050db821dc4df996c0f268615230099cde836e685e5b5465d"
SRC_URI[cargo-snapshot-aarch64.sha256sum] = "8fd2d9806f0601feab1485f79e46d1441af2158c68abf56788ff355d5c6b4ab5"

SRC_URI[rust-std-snapshot-powerpc64le.sha256sum] = "bbd882f9ec7f01a732ecc60cf50b7d8a10cd52c3de41c205f62938b6dc2b4dbc"
SRC_URI[rustc-snapshot-powerpc64le.sha256sum] = "7152b111cf91a2cfa1e7beb51d3c737561095ebdf75ec7e032ab1118639ea4ca"
SRC_URI[cargo-snapshot-powerpc64le.sha256sum] = "5f1751ab8d44a9c9e083d32a8039980d699a1224654e3f5aa0dfffbc4407f1c0"

SRC_URI += " \
    https://static.rust-lang.org/dist/${RUST_STD_SNAPSHOT}.tar.xz;name=rust-std-snapshot-${RUST_BUILD_ARCH};subdir=rust-snapshot-components \
    https://static.rust-lang.org/dist/${RUSTC_SNAPSHOT}.tar.xz;name=rustc-snapshot-${RUST_BUILD_ARCH};subdir=rust-snapshot-components \
    https://static.rust-lang.org/dist/${CARGO_SNAPSHOT}.tar.xz;name=cargo-snapshot-${RUST_BUILD_ARCH};subdir=rust-snapshot-components \
"

RUST_STD_SNAPSHOT = "rust-std-${SNAPSHOT_VERSION}-${RUST_BUILD_ARCH}-unknown-linux-gnu"
RUSTC_SNAPSHOT = "rustc-${SNAPSHOT_VERSION}-${RUST_BUILD_ARCH}-unknown-linux-gnu"
CARGO_SNAPSHOT = "cargo-${SNAPSHOT_VERSION}-${RUST_BUILD_ARCH}-unknown-linux-gnu"
