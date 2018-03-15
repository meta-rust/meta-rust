require rust-cross.inc
require rust-source-${PV}.inc
require rust-snapshot-${PV}.inc

RUST_STD_SNAPSHOT_TARGET = "rust-std-${RS_VERSION}-${RUST_TARGET_SYS}"

SRC_URI += " \
	https://static.rust-lang.org/dist/${RUST_STD_SNAPSHOT_TARGET}.tar.gz;name=rust-std-snapshot-target;subdir=rust-snapshot-components \
"

#arm-unknown-linux-gnueabihf hashes
SRC_URI[rust-std-snapshot-target.md5sum] = "855bf997716027017c4a5b19a59d17be"
SRC_URI[rust-std-snapshot-target.sha256sum] = "61d5654881cacf16d0d40fe0fd9cf0f464acc049643e0458666543928addae1e"
