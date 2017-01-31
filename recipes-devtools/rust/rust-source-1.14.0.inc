# Specifics for Rust 1.14.0

## This is information on the rust-snapshot (binary) used to build our current release.
## snapshot info is taken from rust/src/stage0.txt
## TODO: find a way to add additional SRC_URIs based on the contents of an
##       earlier SRC_URI.
RS_VERSION = "1.13.0"

RUST_SNAPSHOT = "rustc-${RS_VERSION}-${RUST_BUILD_SYS}"

# These are x86_64-unknown-linux-gnu hashes, how can we add more?
SRC_URI[rust-snapshot.md5sum] = "1400262e1529f94a12d2f5c77cc67782"
SRC_URI[rust-snapshot.sha256sum] = "0b092ba6750be89aad32b231ad9c625a11b040fae3cad5aa3ef32aaf213332d4"

SRC_URI += "\
	https://static.rust-lang.org/dist/rustc-${PV}-src.tar.gz;name=rust \
    "
SRC_URI[rust.md5sum] = "00b6bb5b465e7bd89c541eea99876cdc"
SRC_URI[rust.sha256sum] = "c790edd2e915bd01bea46122af2942108479a2fda9a6f76d1094add520ac3b6b"

