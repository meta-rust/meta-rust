SRC_URI[rust.md5sum] = "e853b04d9da15055d1f8f33b45a1ae68"
SRC_URI[rust.sha256sum] = "ea6eb983daf2a073df57186a58f0d4ce0e85c711bec13c627a8c85d51b6a6d78"

## snapshot info taken from rust/src/snapshots.txt
## TODO: find a way to add aditional SRC_URIs based on the contents of an
##       earlier SRC_URI.
RS_DATE = "2015-05-24"
RS_SRCHASH = "ba0e1cd"
# linux-x86_64
RS_ARCH = "linux-x86_64"
RS_HASH = "5fd8698fdfe953e6c4d86cf4fa1d5f3a0053248c"
RUST_SNAPSHOT = "rust-stage0-${RS_DATE}-${RS_SRCHASH}-${RS_ARCH}-${RS_HASH}.tar.bz2"

SRC_URI[rust-snapshot.md5sum] = "04deb393c39d43a2abc68ebac6a0bad2"
SRC_URI[rust-snapshot.sha256sum] = "11f7f56320bd0dff5b47bae3f80377d9514a3ad4bc983d674eb33074c95d66a0"
