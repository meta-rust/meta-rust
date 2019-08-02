## This is information on the rust-snapshot (binary) used to build our current release.
## snapshot info is taken from rust/src/stage0.txt
## TODO: find a way to add additional SRC_URIs based on the contents of an
##       earlier SRC_URI.
RS_VERSION = "1.35.0"

RUSTC_SNAPSHOT = "rustc-${RS_VERSION}-${BUILD_ARCH}-unknown-linux-gnu"
RUST_STD_SNAPSHOT = "rust-std-${RS_VERSION}-${BUILD_ARCH}-unknown-linux-gnu"
CARGO_VERSION = "0.36.0"
CARGO_SNAPSHOT = "cargo-${CARGO_VERSION}-${BUILD_ARCH}-unknown-linux-gnu"

SRC_URI += " \
	https://static.rust-lang.org/dist/${RUSTC_SNAPSHOT}.tar.xz;name=rustc-snapshot-${BUILD_ARCH};subdir=rust-snapshot-components \
	https://static.rust-lang.org/dist/${RUST_STD_SNAPSHOT}.tar.xz;name=rust-std-snapshot-${BUILD_ARCH};subdir=rust-snapshot-components \
	https://static.rust-lang.org/dist/${CARGO_SNAPSHOT}.tar.xz;name=cargo-snapshot-${BUILD_ARCH};subdir=rust-snapshot-components \
	"

# TODO: Add hashes for other architecture toolchains as well. Make a script?
SRC_URI[rustc-snapshot-x86_64.md5sum] = "47ea78f6b3f68e30f24b9c94e465d6bd"
SRC_URI[rustc-snapshot-x86_64.sha256sum] = "5d6dc216ba429ddf3a1657e70f3e5e380549b546fe56de897677a11d72aa4e07"
SRC_URI[rust-std-snapshot-x86_64.md5sum] = "348ec23ca8e47fc65079bc80e63cca5f"
SRC_URI[rust-std-snapshot-x86_64.sha256sum] = "ccff05d0e2d88499505b10f8e33e8b1645df057f918edc81f8acb0fcee9f90b2"
SRC_URI[cargo-snapshot-x86_64.md5sum] = "93a375e771f3d9b3a139e612dd4730ee"
SRC_URI[cargo-snapshot-x86_64.sha256sum] = "ab5a6ff1947463dbd2477ca5dac2012494dae821112098ae0c54add652adfdc3"
