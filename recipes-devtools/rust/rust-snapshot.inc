## This is information on the rust-snapshot (binary) used to build our current release.
## snapshot info is taken from rust/src/stage0.txt
## TODO: find a way to add additional SRC_URIs based on the contents of an
##       earlier SRC_URI.
RS_DATE = "2016-08-16"
RS_VERSION = "1.11.0"
RS_ARCH = "x86_64-unknown-linux-gnu"
RS_KEY = "39b92f95"

RUST_SNAPSHOT = "rustc-${RS_VERSION}-${RS_ARCH}.tar.gz"
RUST_SNAPSHOT_URI = "https://static.rust-lang.org/dist/${RS_DATE}/${RUST_SNAPSHOT}"

SRC_URI[rust-snapshot.md5sum] = "b83d7a1a90c2d80bef97a518022948c8"
SRC_URI[rust-snapshot.sha256sum] = "e9d27a72900da33c1bbd0e59dd42fd6414c6bcdfa33593fb7c7360068406394a"
