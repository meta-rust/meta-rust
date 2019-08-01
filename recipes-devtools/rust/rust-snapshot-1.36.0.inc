## This is information on the rust-snapshot (binary) used to build our current release.
## snapshot info is taken from rust/src/stage0.txt
## TODO: find a way to add additional SRC_URIs based on the contents of an
##       earlier SRC_URI.
RS_VERSION = "1.35.0"

RUST_STD_SNAPSHOT = "rust-std-${RS_VERSION}-${BUILD_ARCH}-unknown-linux-gnu"
RUSTC_SNAPSHOT = "rustc-${RS_VERSION}-${BUILD_ARCH}-unknown-linux-gnu"
CARGO_VERSION = "0.36.0"
CARGO_SNAPSHOT = "cargo-${CARGO_VERSION}-${BUILD_ARCH}-unknown-linux-gnu"

SRC_URI += " \
	https://static.rust-lang.org/dist/${RUST_STD_SNAPSHOT}.tar.gz;name=rust-std-snapshot-${BUILD_ARCH};subdir=rust-snapshot-components \
	https://static.rust-lang.org/dist/${RUSTC_SNAPSHOT}.tar.gz;name=rustc-snapshot-${BUILD_ARCH};subdir=rust-snapshot-components \
	https://static.rust-lang.org/dist/${CARGO_SNAPSHOT}.tar.gz;name=cargo-snapshot-${BUILD_ARCH};subdir=rust-snapshot-components \
	"

# TODO: Add hashes for other architecture toolchains as well. Make a script?
SRC_URI[rustc-snapshot-x86_64.md5sum] = "2942b5ffa86e243b46f20fe3ac2f4d64"
SRC_URI[rustc-snapshot-x86_64.sha256sum] = "bb3a07a1f2fdc3eeeee25fc40131d3f05494e3838dfd4e9275475ffc500d7a9e"
SRC_URI[rust-std-snapshot-x86_64.md5sum] = "5c58d2b6b7d9b9a600d36742b5391b94"
SRC_URI[rust-std-snapshot-x86_64.sha256sum] = "5dfa92661ff1a22680785bd6999b6117ae66841e2bd9e5318eb97002956131e4"
SRC_URI[cargo-snapshot-x86_64.md5sum] = "79aae88fdbee04d5d89eec76fef67c10"
SRC_URI[cargo-snapshot-x86_64.sha256sum] = "77586f2fb5b6f6caef0cb6d3cc32a18559d4fcd6a6db4e75f4b3fb7adb050437"
