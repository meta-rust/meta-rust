# Specifics for Rust 1.12.1

## This is information on the rust-snapshot (binary) used to build our current release.
## snapshot info is taken from rust/src/stage0.txt
## TODO: find a way to add additional SRC_URIs based on the contents of an
##       earlier SRC_URI.
RS_VERSION = "1.11.0"
RS_KEY = "5c6cf767"

RUST_SNAPSHOT = "rustc-${RS_VERSION}-${RUST_BUILD_SYS}"

# These are x86_64-unknown-linux-gnu hashes, how can we add more?
SRC_URI[rust-snapshot.md5sum] = "b83d7a1a90c2d80bef97a518022948c8"
SRC_URI[rust-snapshot.sha256sum] = "e9d27a72900da33c1bbd0e59dd42fd6414c6bcdfa33593fb7c7360068406394a"

SRC_URI += "\
	https://static.rust-lang.org/dist/rustc-${PV}-src.tar.gz;name=rust \
    "
SRC_URI[rust.md5sum] = "82db5a9cb9a051bf8ece2f5174cb273b"
SRC_URI[rust.sha256sum] = "97913ae4cb255618aaacd1a534b11f343634b040b32656250d09d8d9ec02d3dc"

# later versions of rust change the directory that they unextract to
RUSTSRC = "${WORKDIR}/rustc-${PV}"
# set this as our default
S = "${RUSTSRC}"
