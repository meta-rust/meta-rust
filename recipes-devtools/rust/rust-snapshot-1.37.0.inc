## This is information on the rust-snapshot (binary) used to build our current release.
## snapshot info is taken from rust/src/stage0.txt
## TODO: find a way to add additional SRC_URIs based on the contents of an
##       earlier SRC_URI.
RS_VERSION = "1.36.0"

RUSTC_SNAPSHOT = "rustc-${RS_VERSION}-${BUILD_ARCH}-unknown-linux-gnu"
RUST_STD_SNAPSHOT = "rust-std-${RS_VERSION}-${BUILD_ARCH}-unknown-linux-gnu"
CARGO_VERSION = "0.37.0"
CARGO_SNAPSHOT = "cargo-${CARGO_VERSION}-${BUILD_ARCH}-unknown-linux-gnu"

SRC_URI += " \
	https://static.rust-lang.org/dist/${RUSTC_SNAPSHOT}.tar.xz;name=rustc-snapshot-${BUILD_ARCH};subdir=rust-snapshot-components \
	https://static.rust-lang.org/dist/${RUST_STD_SNAPSHOT}.tar.xz;name=rust-std-snapshot-${BUILD_ARCH};subdir=rust-snapshot-components \
	https://static.rust-lang.org/dist/${CARGO_SNAPSHOT}.tar.xz;name=cargo-snapshot-${BUILD_ARCH};subdir=rust-snapshot-components \
	"

# TODO: Add hashes for other architecture toolchains as well. Make a script?
SRC_URI[rustc-snapshot-x86_64.md5sum] = "ec27794c94cc1df1a0a69f7244a09176"
SRC_URI[rustc-snapshot-x86_64.sha256sum] = "fff0158da6f5af2a89936dc3e0c361077c06c2983eb310615e02f81ebbde1416"
SRC_URI[rust-std-snapshot-x86_64.md5sum] = "b71a6fd6f44527c3bf09584e89ad8958"
SRC_URI[rust-std-snapshot-x86_64.sha256sum] = "ce8e12684b568a8a4f7d346a743383429849cf3f028f5712ad3d3e31590c8db3"
SRC_URI[cargo-snapshot-x86_64.md5sum] = "8c661276a0da7a1aa48affbe33b347e6"
SRC_URI[cargo-snapshot-x86_64.sha256sum] = "d20fa121951339d5492cf8862f8a7af59efc99d18f3c27b95ab6d4658b6a7d67"
