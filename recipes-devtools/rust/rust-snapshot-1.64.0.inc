## This is information on the rust-snapshot (binary) used to build our current release.
## snapshot info is taken from rust/src/stage0.json
## TODO: find a way to add additional SRC_URIs based on the contents of an
##       earlier SRC_URI.
RS_VERSION = "1.63.0"
CARGO_VERSION = "1.63.0"

# TODO: Add hashes for other architecture toolchains as well. Make a script?
SRC_URI[rust-std-snapshot-x86_64.sha256sum] = "993c2c17bf76ac626bfb5b17bddce65fbdfc14f70d183f33773de0cd12df46d2"
SRC_URI[rustc-snapshot-x86_64.sha256sum] = "bdab9d9afa5c329c40f9ba568364815237fab8426477c12bfabad35ffc484ab5"
SRC_URI[cargo-snapshot-x86_64.sha256sum] = "f370d12e4c11f0c835becb738bcf00d363f29b76f8b424b4dcb005abcf15fc9a"

SRC_URI[rust-std-snapshot-aarch64.sha256sum] = "f1d93b3d48258f701687c63ef9b226c07329fb92c2c5559283258687f958e9d0"
SRC_URI[rustc-snapshot-aarch64.sha256sum] = "d78799bb8f4177877f97b9051c9cba1fd85173f2e9cecab9486388fc6fa66259"
SRC_URI[cargo-snapshot-aarch64.sha256sum] = "4313ab44dccba4faed20db4aacc16def405773d1676e79d3e65ced4b99d710d4"

SRC_URI += " \
    https://static.rust-lang.org/dist/${RUST_STD_SNAPSHOT}.tar.xz;name=rust-std-snapshot-${BUILD_ARCH};subdir=rust-snapshot-components \
    https://static.rust-lang.org/dist/${RUSTC_SNAPSHOT}.tar.xz;name=rustc-snapshot-${BUILD_ARCH};subdir=rust-snapshot-components \
    https://static.rust-lang.org/dist/${CARGO_SNAPSHOT}.tar.xz;name=cargo-snapshot-${BUILD_ARCH};subdir=rust-snapshot-components \
"

RUST_STD_SNAPSHOT = "rust-std-${RS_VERSION}-${BUILD_ARCH}-unknown-linux-gnu"
RUSTC_SNAPSHOT = "rustc-${RS_VERSION}-${BUILD_ARCH}-unknown-linux-gnu"
CARGO_SNAPSHOT = "cargo-${CARGO_VERSION}-${BUILD_ARCH}-unknown-linux-gnu"
