## This is information on the rust-snapshot (binary) used to build our current release.
## snapshot info is taken from rust/src/stage0
## Rust is self-hosting and bootstraps itself with a pre-built previous version of itself.
## The exact (previous) version that has been used is specified in the source tarball.
## The version is replicated here.
## TODO: find a way to add additional SRC_URIs based on the contents of an
##       earlier SRC_URI.

SNAPSHOT_VERSION = "1.81.0"

# TODO: Add hashes for other architecture toolchains as well.

# You can use scripts/rust-get-stage0.sh to update hashes
SRC_URI[rust-std-snapshot-x86_64.sha256sum] = "6ddf80f254e8eea9956308ba89fd68e1ac7885853df9239b07bbc9f047b7562f"
SRC_URI[rustc-snapshot-x86_64.sha256sum]    = "988a4e4cdecebe4f4a0c52ec4ade5a5bfc58d6958969f5b1e8aac033bda2613e"
SRC_URI[cargo-snapshot-x86_64.sha256sum]    = "c50ee4b1ae8695461930e36d5465dddb7c7a0e0f0aa6cbd60de120b17c38b841"

SRC_URI[rust-std-snapshot-aarch64.sha256sum] = "85567f037cee338f8ec8f9b6287a7f200d221658a996cba254abc91606ece6f4"
SRC_URI[rustc-snapshot-aarch64.sha256sum]    = "301f651f38f8c52ebaad0ac7eb211a5ea25c3b690686d1c265febeee62d2c6fc"
SRC_URI[cargo-snapshot-aarch64.sha256sum]    = "76f8927e4923c26c51b60ef99a29f3609843b3a2730f0bdf2ea6958626f11b11"

SRC_URI[rust-std-snapshot-powerpc64le.sha256sum] = "5ba237cfbd18806bf77fbe8bc31b14a17f3d14acb30a022955cf047eb8d41056"
SRC_URI[rustc-snapshot-powerpc64le.sha256sum]    = "734f407345b05617d62a30d96d8305b51b7cf7de3b1bdc160449726ea8f51ae0"
SRC_URI[cargo-snapshot-powerpc64le.sha256sum]    = "813d2dcd603a1ad65a5de77515f4c94fdae301a1e1e8afcc2541076eebaba848"

SRC_URI += " \
    https://static.rust-lang.org/dist/${RUST_STD_SNAPSHOT}.tar.xz;name=rust-std-snapshot-${RUST_BUILD_ARCH};subdir=rust-snapshot-components \
    https://static.rust-lang.org/dist/${RUSTC_SNAPSHOT}.tar.xz;name=rustc-snapshot-${RUST_BUILD_ARCH};subdir=rust-snapshot-components \
    https://static.rust-lang.org/dist/${CARGO_SNAPSHOT}.tar.xz;name=cargo-snapshot-${RUST_BUILD_ARCH};subdir=rust-snapshot-components \
"

RUST_STD_SNAPSHOT = "rust-std-${SNAPSHOT_VERSION}-${RUST_BUILD_ARCH}-unknown-linux-gnu"
RUSTC_SNAPSHOT = "rustc-${SNAPSHOT_VERSION}-${RUST_BUILD_ARCH}-unknown-linux-gnu"
CARGO_SNAPSHOT = "cargo-${SNAPSHOT_VERSION}-${RUST_BUILD_ARCH}-unknown-linux-gnu"
