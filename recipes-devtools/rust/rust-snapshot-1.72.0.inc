## This is information on the rust-snapshot (binary) used to build our current release.
## snapshot info is taken from rust/src/stage0.json
## Rust is self-hosting and bootstraps itself with a pre-built previous version of itself.
## The exact (previous) version that has been used is specified in the source tarball.
## The version is replicated here.
## TODO: find a way to add additional SRC_URIs based on the contents of an
##       earlier SRC_URI.

SNAPSHOT_VERSION = "1.71.0"

# TODO: Add hashes for other architecture toolchains as well. Make a script?
SRC_URI[rust-std-snapshot-x86_64.sha256sum] = "98ae6530c3a41167e9d93d11ea078be98a02f6d809a06d0d51af3ce0f73150d7"
SRC_URI[rustc-snapshot-x86_64.sha256sum] = "c293d906769671d1cd18e945671bbd14e0b8a41df5075c47f33e6086fc8a1558"
SRC_URI[cargo-snapshot-x86_64.sha256sum] = "fe6fb520f59966300ee661d18b37c36cb3e614877c4c01dfedf987b8a9c577e9"

SRC_URI[rust-std-snapshot-aarch64.sha256sum] = "58542a0ab1162ce05a45eb751793782dc24c5bf8eb9a7467317f254260305ea6"
SRC_URI[rustc-snapshot-aarch64.sha256sum] = "e61b6e34df8c3a002798a9f627c4da701d66f9fc066a70264e354b03d06e6722"
SRC_URI[cargo-snapshot-aarch64.sha256sum] = "13e8ff23d6af976a45f3ab451bf698e318a8d1823d588ff8a989555096f894a8"

SRC_URI[rust-std-snapshot-powerpc64le.sha256sum] = "3ce73e032232522cd7c37e64b1e8895f16ddcef02b1646d078f67bb36b6c1494"
SRC_URI[rustc-snapshot-powerpc64le.sha256sum] = "9c4e3d5740e48265ab59888090013793777a526ecf5541c0fb055f9f0a13f409"
SRC_URI[cargo-snapshot-powerpc64le.sha256sum] = "9e6e184ad1836f52e5863b6ed72619926bb2e8c7ccf2b3c96bf86d7783f19673"

SRC_URI += " \
    https://static.rust-lang.org/dist/${RUST_STD_SNAPSHOT}.tar.xz;name=rust-std-snapshot-${RUST_BUILD_ARCH};subdir=rust-snapshot-components \
    https://static.rust-lang.org/dist/${RUSTC_SNAPSHOT}.tar.xz;name=rustc-snapshot-${RUST_BUILD_ARCH};subdir=rust-snapshot-components \
    https://static.rust-lang.org/dist/${CARGO_SNAPSHOT}.tar.xz;name=cargo-snapshot-${RUST_BUILD_ARCH};subdir=rust-snapshot-components \
"

RUST_STD_SNAPSHOT = "rust-std-${SNAPSHOT_VERSION}-${RUST_BUILD_ARCH}-unknown-linux-gnu"
RUSTC_SNAPSHOT = "rustc-${SNAPSHOT_VERSION}-${RUST_BUILD_ARCH}-unknown-linux-gnu"
CARGO_SNAPSHOT = "cargo-${SNAPSHOT_VERSION}-${RUST_BUILD_ARCH}-unknown-linux-gnu"
