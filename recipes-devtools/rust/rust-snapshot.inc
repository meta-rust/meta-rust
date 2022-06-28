## This is information on the rust-snapshot (binary) used to build our current release.
## snapshot info is taken from rust/src/stage0.txt
## TODO: find a way to add additional SRC_URIs based on the contents of an
##       earlier SRC_URI.
RS_VERSION = "1.60.0"
CARGO_VERSION = "1.60.0"

# TODO: Add hashes for other architecture toolchains as well. Make a script?
SRC_URI[rust-std-snapshot-x86_64.sha256sum] = "6fb8ee3650beb10836ae48a9aaa535473e64eaca20695b88113267aea3c7557f"
SRC_URI[rustc-snapshot-x86_64.sha256sum] = "fc0b41c15e348ad0eeb7a6c015a922a2ac95e9577e531635558b26d99399f315"
SRC_URI[cargo-snapshot-x86_64.sha256sum] = "48edb2eb51d7c56ef9a3130f0b331e83f139559161f6f93b9588d28cf72610f3"

SRC_URI[rust-std-snapshot-aarch64.sha256sum] = "fbc39c2ba2eee9bad7305d73d02a63ada651961be8fd9e0dae520bda5d715c6e"
SRC_URI[rustc-snapshot-aarch64.sha256sum] = "f5b24f2bc30db4b8efb7eba7db86fd5db0bc283631b4c918794e9217fca32822"
SRC_URI[cargo-snapshot-aarch64.sha256sum] = "36030f5cede7971eaed45284b5243b4103184a663ad934124de8a530e0e6d993"

SRC_URI += " \
    https://static.rust-lang.org/dist/${RUST_STD_SNAPSHOT}.tar.xz;name=rust-std-snapshot-${BUILD_ARCH};subdir=rust-snapshot-components \
    https://static.rust-lang.org/dist/${RUSTC_SNAPSHOT}.tar.xz;name=rustc-snapshot-${BUILD_ARCH};subdir=rust-snapshot-components \
    https://static.rust-lang.org/dist/${CARGO_SNAPSHOT}.tar.xz;name=cargo-snapshot-${BUILD_ARCH};subdir=rust-snapshot-components \
"

RUST_STD_SNAPSHOT = "rust-std-${RS_VERSION}-${BUILD_ARCH}-unknown-linux-gnu"
RUSTC_SNAPSHOT = "rustc-${RS_VERSION}-${BUILD_ARCH}-unknown-linux-gnu"
CARGO_SNAPSHOT = "cargo-${CARGO_VERSION}-${BUILD_ARCH}-unknown-linux-gnu"
