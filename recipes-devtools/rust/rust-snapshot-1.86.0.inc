## This is information on the rust-snapshot (binary) used to build our current release.
## snapshot info is taken from rust/src/stage0
## Rust is self-hosting and bootstraps itself with a pre-built previous version of itself.
## The exact (previous) version that has been used is specified in the source tarball.
## The version is replicated here.
## TODO: find a way to add additional SRC_URIs based on the contents of an
##       earlier SRC_URI.

SNAPSHOT_VERSION = "1.85.0"

# TODO: Add hashes for other architecture toolchains as well.

# You can use scripts/rust-get-stage0.sh to update hashes
SRC_URI[rust-std-snapshot-x86_64.sha256sum] = "285e105d25ebdf501341238d4c0594ecdda50ec9078f45095f793a736b1f1ac2"
SRC_URI[rustc-snapshot-x86_64.sha256sum] = "7436f13797475082cd87aa65547449e01659d6a810b4cd5f8aedc48bb9f89dfb"
SRC_URI[cargo-snapshot-x86_64.sha256sum] = "0aff33b57b0e0b102d762a2b53042846c1ca346cff4b7bd96b5c03c9e8e51d81"

SRC_URI[rust-std-snapshot-aarch64.sha256sum] = "8af1d793f7820e9ad0ee23247a9123542c3ea23f8857a018651c7788af9bc5b7"
SRC_URI[rustc-snapshot-aarch64.sha256sum] = "e742b768f67303010b002b515f6613c639e69ffcc78cd0857d6fe7989e9880f6"
SRC_URI[cargo-snapshot-aarch64.sha256sum] = "cdebe48b066d512d664c13441e8fae2d0f67106c2080aa44289d98b24192b8bc"

SRC_URI[rust-std-snapshot-powerpc64le.sha256sum] = "d0cfda4e18623d17922eb367e44ac9549ab3d5fe1c0bdbe0c2c95754255fa705"
SRC_URI[rustc-snapshot-powerpc64le.sha256sum] = "371e40f9d6d82aecb056f70f82868d98ddc1c20510aa7d388442ac8d2d86a6ca"
SRC_URI[cargo-snapshot-powerpc64le.sha256sum] = "e1469f4249a7e21f872af487dcd1bd10ce388b5b3679bdab0cb0965e1e30fe47"

SRC_URI += " \
    https://static.rust-lang.org/dist/${RUST_STD_SNAPSHOT}.tar.xz;name=rust-std-snapshot-${RUST_BUILD_ARCH};subdir=rust-snapshot-components \
    https://static.rust-lang.org/dist/${RUSTC_SNAPSHOT}.tar.xz;name=rustc-snapshot-${RUST_BUILD_ARCH};subdir=rust-snapshot-components \
    https://static.rust-lang.org/dist/${CARGO_SNAPSHOT}.tar.xz;name=cargo-snapshot-${RUST_BUILD_ARCH};subdir=rust-snapshot-components \
"

RUST_STD_SNAPSHOT = "rust-std-${SNAPSHOT_VERSION}-${RUST_BUILD_ARCH}-unknown-linux-gnu"
RUSTC_SNAPSHOT = "rustc-${SNAPSHOT_VERSION}-${RUST_BUILD_ARCH}-unknown-linux-gnu"
CARGO_SNAPSHOT = "cargo-${SNAPSHOT_VERSION}-${RUST_BUILD_ARCH}-unknown-linux-gnu"
