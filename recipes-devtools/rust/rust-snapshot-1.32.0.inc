## This is information on the rust-snapshot (binary) used to build our current release.
## snapshot info is taken from rust/src/stage0.txt
## TODO: find a way to add additional SRC_URIs based on the contents of an
##       earlier SRC_URI.
RS_VERSION = "1.31.1"

RUST_STD_SNAPSHOT = "rust-std-${RS_VERSION}-${BUILD_ARCH}-unknown-linux-gnu"
RUSTC_SNAPSHOT = "rustc-${RS_VERSION}-${BUILD_ARCH}-unknown-linux-gnu"
CARGO_VERSION = "0.32.0"
CARGO_SNAPSHOT = "cargo-${CARGO_VERSION}-${BUILD_ARCH}-unknown-linux-gnu"

SRC_URI += " \
	https://static.rust-lang.org/dist/${RUST_STD_SNAPSHOT}.tar.gz;name=rust-std-snapshot-${BUILD_ARCH};subdir=rust-snapshot-components \
	https://static.rust-lang.org/dist/${RUSTC_SNAPSHOT}.tar.gz;name=rustc-snapshot-${BUILD_ARCH};subdir=rust-snapshot-components \
	https://static.rust-lang.org/dist/${CARGO_SNAPSHOT}.tar.gz;name=cargo-snapshot-${BUILD_ARCH};subdir=rust-snapshot-components \
	"

# TODO: Add hashes for other architecture toolchains as well. Make a script?
SRC_URI[rustc-snapshot-x86_64.md5sum] = "83f3f130e9a1c7e855a0c1eed8ac3508"
SRC_URI[rustc-snapshot-x86_64.sha256sum] = "77d47ce7e27a146e4301f11befd43f3fc5ac195ace0dfc07ac8154f130b057ea"
SRC_URI[rust-std-snapshot-x86_64.md5sum] = "3115e11612a882713978279635116881"
SRC_URI[rust-std-snapshot-x86_64.sha256sum] = "699664b3a64959a2d75e486e19e7cc9934cbcbf2c57a977dd2a2b33cff367da1"
SRC_URI[cargo-snapshot-x86_64.md5sum] = "9ae6d258781870591450ea33d3b1bed9"
SRC_URI[cargo-snapshot-x86_64.sha256sum] = "b3d3dc57182fb173ecf367f7884dceb855a096d9b9b32eba994e3359ddc68cd4"
