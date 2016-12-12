# Specifics for Rust 1.10.0

## snapshot info taken from rust/src/stage0.txt
## TODO: find a way to add additional SRC_URIs based on the contents of an
##       earlier SRC_URI.
RS_VERSION = "1.9.0"
RS_KEY = "e8edd0fd"

RUST_SNAPSHOT = "rustc-${RS_VERSION}-${RUST_BUILD_SYS}"

# These are x86_64-unknown-linux-gnu hashes, how can we add more?
SRC_URI[rust-snapshot.md5sum] = "f1cf6d2fe15e4be18a08259f1540a4ae"
SRC_URI[rust-snapshot.sha256sum] = "d0704d10237c66c3efafa6f7e5570c59a1d3fe5c6d99487540f90ebb37cd84c4"

SRC_URI[rust.md5sum] = "a48fef30353fc9daa70b484b690ce5db"
SRC_URI[rust.sha256sum] = "a4015aacf4f6d8a8239253c4da46e7abaa8584f8214d1828d2ff0a8f56176869"

