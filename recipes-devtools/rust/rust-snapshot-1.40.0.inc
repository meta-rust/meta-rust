## This is information on the rust-snapshot (binary) used to build our current release.
## snapshot info is taken from rust/src/stage0.txt
## TODO: find a way to add additional SRC_URIs based on the contents of an
##       earlier SRC_URI.
RS_VERSION = "1.39.0"

RUSTC_SNAPSHOT = "rustc-${RS_VERSION}-${BUILD_ARCH}-unknown-linux-gnu"
RUST_STD_SNAPSHOT = "rust-std-${RS_VERSION}-${BUILD_ARCH}-unknown-linux-gnu"
CARGO_VERSION = "0.40.0"
CARGO_SNAPSHOT = "cargo-${CARGO_VERSION}-${BUILD_ARCH}-unknown-linux-gnu"

SRC_URI += " \
	https://static.rust-lang.org/dist/${RUSTC_SNAPSHOT}.tar.xz;name=rustc-snapshot-${BUILD_ARCH};subdir=rust-snapshot-components \
	https://static.rust-lang.org/dist/${RUST_STD_SNAPSHOT}.tar.xz;name=rust-std-snapshot-${BUILD_ARCH};subdir=rust-snapshot-components \
	https://static.rust-lang.org/dist/${CARGO_SNAPSHOT}.tar.xz;name=cargo-snapshot-${BUILD_ARCH};subdir=rust-snapshot-components \
	"

# TODO: Add hashes for other architecture toolchains as well. Make a script?
SRC_URI[rustc-snapshot-x86_64.md5sum] = "aa10585498675e44be219d3644c15853"
SRC_URI[rustc-snapshot-x86_64.sha256sum] = "5b2a435a4c034615d70cfc383abe9924cbd1ffd4669caa55ce6539f22ed979ed"
SRC_URI[rust-std-snapshot-x86_64.md5sum] = "d8b8e6f1a5a255d22b9f86c97a65049f"
SRC_URI[rust-std-snapshot-x86_64.sha256sum] = "b629952ec9e3e750137d7b8a922de145c97c1dc372dd616e86e4e501da13910b"
SRC_URI[cargo-snapshot-x86_64.md5sum] = "a51643b8980bcaefa9043715a8e9a2ba"
SRC_URI[cargo-snapshot-x86_64.sha256sum] = "7b9ba52c252964724f49aab49e42bec62fca929297ef058412c7e727b0794620"
