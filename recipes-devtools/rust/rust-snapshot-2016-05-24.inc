## snapshot info taken from rust/src/stage0.txt
## TODO: find a way to add additional SRC_URIs based on the contents of an
##       earlier SRC_URI.
RS_DATE = "2016-05-24"
RS_VERSION = "1.9.0"
RS_ARCH = "x86_64-unknown-linux-gnu"

RUST_SNAPSHOT = "rustc-${RS_VERSION}-${RS_ARCH}.tar.gz"
RUST_SNAPSHOT_URI = "https://static.rust-lang.org/dist/${RS_DATE}/${RUST_SNAPSHOT}"

SRC_URI[rust-snapshot.md5sum] = "f1cf6d2fe15e4be18a08259f1540a4ae"
SRC_URI[rust-snapshot.sha256sum] = "d0704d10237c66c3efafa6f7e5570c59a1d3fe5c6d99487540f90ebb37cd84c4"

