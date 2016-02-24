## snapshot info taken from rust/src/snapshots.txt
## TODO: find a way to add additional SRC_URIs based on the contents of an
##       earlier SRC_URI.
RS_DATE = "2015-08-11"
RS_SRCHASH = "1af31d4"
# linux-x86_64
RS_ARCH = "linux-x86_64"
RS_HASH = "7df8ba9dec63ec77b857066109d4b6250f3d222f"

RUST_SNAPSHOT = "rust-stage0-${RS_DATE}-${RS_SRCHASH}-${RS_ARCH}-${RS_HASH}.tar.bz2"

SRC_URI[rust-snapshot.md5sum] = "53b2e1f553eaeb88e8d60d5380670283"
SRC_URI[rust-snapshot.sha256sum] = "5936f5ec4327d41f3aa9f98cbedebb6fd3d72715f8df578e0c9a669154c80bc3"

