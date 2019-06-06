## This is information on the rust-snapshot (binary) used to build our current release.
## snapshot info is taken from rust/src/stage0.txt
## TODO: find a way to add additional SRC_URIs based on the contents of an
##       earlier SRC_URI.
RS_VERSION = "1.33.0"

RUST_STD_SNAPSHOT = "rust-std-${RS_VERSION}-${BUILD_ARCH}-unknown-linux-gnu"
RUSTC_SNAPSHOT = "rustc-${RS_VERSION}-${BUILD_ARCH}-unknown-linux-gnu"
CARGO_VERSION = "0.34.0"
CARGO_SNAPSHOT = "cargo-${CARGO_VERSION}-${BUILD_ARCH}-unknown-linux-gnu"

SRC_URI += " \
	https://static.rust-lang.org/dist/${RUST_STD_SNAPSHOT}.tar.gz;name=rust-std-snapshot-${BUILD_ARCH};subdir=rust-snapshot-components \
	https://static.rust-lang.org/dist/${RUSTC_SNAPSHOT}.tar.gz;name=rustc-snapshot-${BUILD_ARCH};subdir=rust-snapshot-components \
	https://static.rust-lang.org/dist/${CARGO_SNAPSHOT}.tar.gz;name=cargo-snapshot-${BUILD_ARCH};subdir=rust-snapshot-components \
	"

# TODO: Add hashes for other architecture toolchains as well. Make a script?
SRC_URI[rustc-snapshot-x86_64.md5sum] = "c1ec989c1965dce754dda1e54274a68c"
SRC_URI[rustc-snapshot-x86_64.sha256sum] = "54a342f718b712d8a17fd7878ebd37d22a82ebc70b59c421168cd4153fd04c2b"
SRC_URI[rust-std-snapshot-x86_64.md5sum] = "d573c5bd3a965c973734c1606968a91e"
SRC_URI[rust-std-snapshot-x86_64.sha256sum] = "661c2ba717ae1502f002b4c6e7aeb8941685c7ea8fe7ac26ed9ede26f615b7af"
SRC_URI[cargo-snapshot-x86_64.md5sum] = "de0e635afa9bf495cefecea476bfce36"
SRC_URI[cargo-snapshot-x86_64.sha256sum] = "4795ae5ca3bb8c7c83ca338676bb02b670efa1eb474e346284b629dc872bcce8"
