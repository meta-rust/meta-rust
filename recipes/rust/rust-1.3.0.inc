SRC_URI[rust.md5sum] = "ffb3971cc96eccaf2de202f621fd415f"
SRC_URI[rust.sha256sum] = "ea02d7bc9e7de5b8be3fe6b37ea9b2bd823f9a532c8e4c47d02f37f24ffa3126"

## snapshot info taken from rust/src/snapshots.txt
## TODO: find a way to add aditional SRC_URIs based on the contents of an
##       earlier SRC_URI.
RS_DATE = "2015-07-26"
RS_SRCHASH = "a5c12f4"
# linux-x86_64
RS_ARCH = "linux-x86_64"
RS_HASH = "e451e3bd6e5fcef71e41ae6f3da9fb1cf0e13a0c"
RUST_SNAPSHOT = "rust-stage0-${RS_DATE}-${RS_SRCHASH}-${RS_ARCH}-${RS_HASH}.tar.bz2"

SRC_URI[rust-snapshot.md5sum] = "8f804ec5cebf370c59563a2b35a808cb"
SRC_URI[rust-snapshot.sha256sum] = "779943595dd63d6869c747e2a31c13095f9c5354d4530327d6f9310cc580c2ff"

LIC_FILES_CHKSUM = "file://COPYRIGHT;md5=b1ab5514343f97198b323e33779470a3"
