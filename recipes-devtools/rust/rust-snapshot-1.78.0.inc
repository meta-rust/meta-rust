## This is information on the rust-snapshot (binary) used to build our current release.
## snapshot info is taken from rust/src/stage0.json
## Rust is self-hosting and bootstraps itself with a pre-built previous version of itself.
## The exact (previous) version that has been used is specified in the source tarball.
## The version is replicated here.
## TODO: find a way to add additional SRC_URIs based on the contents of an
##       earlier SRC_URI.

SNAPSHOT_VERSION = "1.77.0"

# TODO: Add hashes for other architecture toolchains as well.

# You can use scripts/rust-get-stage0.sh to update hashes
SRC_URI[rust-std-snapshot-x86_64.sha256sum] = "e5fec840744c3ff63611f6801de80f5ec8e099fa8225bf46d064810a9545e9b5"
SRC_URI[rustc-snapshot-x86_64.sha256sum]    = "89397dddb99733bad987e9fdc9d985a150af2e39c81766099e584d93991f5752"
SRC_URI[cargo-snapshot-x86_64.sha256sum]    = "0af971f126e0307d4e4d974f0e9c33fd1c2923274b14a0861823b5a019e8faf5"

SRC_URI[rust-std-snapshot-aarch64.sha256sum] = "b6c551baf0cc9a32582f2362379b596f33c1bc93ae520d5648e9138de1b4b90b"
SRC_URI[rustc-snapshot-aarch64.sha256sum]    = "ca7caef0b4e32f769edf4d7d596d0da9c3d562dd8233bd9068d3ba6cfe8dfe48"
SRC_URI[cargo-snapshot-aarch64.sha256sum]    = "0833e133e2b98d840c5180a3dabc49c0de9895c54055dfee92fa94d2a12196d5"

SRC_URI[rust-std-snapshot-powerpc64le.sha256sum] = "deffffaaa58b9464719fe4609ccad5db14e482aa48c3dcdb0a8aea62bb82332c"
SRC_URI[rustc-snapshot-powerpc64le.sha256sum]    = "381bd57fd07e6f93e56893091b8aaf0d097b9957d655c2dfbaeff35b2305ea29"
SRC_URI[cargo-snapshot-powerpc64le.sha256sum]    = "a4c4421fe3037522908de081cc0577baaf75e7b8c532616ce79dd032a42c60e8"

SRC_URI += " \
    https://static.rust-lang.org/dist/${RUST_STD_SNAPSHOT}.tar.xz;name=rust-std-snapshot-${RUST_BUILD_ARCH};subdir=rust-snapshot-components \
    https://static.rust-lang.org/dist/${RUSTC_SNAPSHOT}.tar.xz;name=rustc-snapshot-${RUST_BUILD_ARCH};subdir=rust-snapshot-components \
    https://static.rust-lang.org/dist/${CARGO_SNAPSHOT}.tar.xz;name=cargo-snapshot-${RUST_BUILD_ARCH};subdir=rust-snapshot-components \
"

RUST_STD_SNAPSHOT = "rust-std-${SNAPSHOT_VERSION}-${RUST_BUILD_ARCH}-unknown-linux-gnu"
RUSTC_SNAPSHOT = "rustc-${SNAPSHOT_VERSION}-${RUST_BUILD_ARCH}-unknown-linux-gnu"
CARGO_SNAPSHOT = "cargo-${SNAPSHOT_VERSION}-${RUST_BUILD_ARCH}-unknown-linux-gnu"
