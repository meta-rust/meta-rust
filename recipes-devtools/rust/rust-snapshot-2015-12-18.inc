## snapshot info taken from rust/src/snapshots.txt
## TODO: find a way to add additional SRC_URIs based on the contents of an
##       earlier SRC_URI.
RS_DATE = "2015-12-18"
RS_SRCHASH = "3391630"
# linux-x86_64
RS_ARCH = "linux-x86_64"
RS_HASH = "97e2a5eb8904962df8596e95d6e5d9b574d73bf4"

RUST_SNAPSHOT = "rust-stage0-${RS_DATE}-${RS_SRCHASH}-${RS_ARCH}-${RS_HASH}.tar.bz2"

SRC_URI[rust-snapshot.md5sum] = "5c29eb06c8b6ce6ff52f544f31efabe1"
SRC_URI[rust-snapshot.sha256sum] = "a8dc5203673ce43f47316beb02ee0c427edb7bbde2ab5fc662a06b52db2950e7"

