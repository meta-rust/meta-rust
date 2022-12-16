## This is information on the rust-snapshot (binary) used to build our current release.
## snapshot info is taken from rust/src/stage0.json
## TODO: find a way to add additional SRC_URIs based on the contents of an
##       earlier SRC_URI.
RS_VERSION = "1.65.0"
CARGO_VERSION = "1.65.0"

# TODO: Add hashes for other architecture toolchains as well. Make a script?
SRC_URI[rust-std-snapshot-x86_64.sha256sum] = "2b588cd2d49688c0c33b7466614123e8fe4c910f4d802fc0ff0662b1772816a9"
SRC_URI[rustc-snapshot-x86_64.sha256sum] = "62b89786e195fc5a8a262f83118d6689832b24228c9d303cba8ac14dc1e9adc8"
SRC_URI[cargo-snapshot-x86_64.sha256sum] = "82547aacaf42fc3c2970ec31b96751dfbeba3dffe1a042a3780bd670c29a89bf"

SRC_URI[rust-std-snapshot-aarch64.sha256sum] = "735b681c8a6e60925c76d6cc899e78b4cb4562ada24a1f265b2021c1faad78ad"
SRC_URI[rustc-snapshot-aarch64.sha256sum] = "67c3d3545fd898c1383071c0f6296453565e0da10903c50652d7bf679b53e8a2"
SRC_URI[cargo-snapshot-aarch64.sha256sum] = "3fd483c0d58673ab69862824408c8a48612827ddcdeaaca0f8fbe5ca02214a4c"

SRC_URI += " \
    https://static.rust-lang.org/dist/${RUST_STD_SNAPSHOT}.tar.xz;name=rust-std-snapshot-${BUILD_ARCH};subdir=rust-snapshot-components \
    https://static.rust-lang.org/dist/${RUSTC_SNAPSHOT}.tar.xz;name=rustc-snapshot-${BUILD_ARCH};subdir=rust-snapshot-components \
    https://static.rust-lang.org/dist/${CARGO_SNAPSHOT}.tar.xz;name=cargo-snapshot-${BUILD_ARCH};subdir=rust-snapshot-components \
"

RUST_STD_SNAPSHOT = "rust-std-${RS_VERSION}-${BUILD_ARCH}-unknown-linux-gnu"
RUSTC_SNAPSHOT = "rustc-${RS_VERSION}-${BUILD_ARCH}-unknown-linux-gnu"
CARGO_SNAPSHOT = "cargo-${CARGO_VERSION}-${BUILD_ARCH}-unknown-linux-gnu"
