require rust-snapshot.inc

## This is information on the rust-snapshot (binary) used to build our current release.
## snapshot info is taken from rust/src/stage0.txt
## TODO: find a way to add additional SRC_URIs based on the contents of an
##       earlier SRC_URI.
RS_VERSION = "1.50.0"
CARGO_VERSION = "1.50.0"

# TODO: Add hashes for other architecture toolchains as well. Make a script?
SRC_URI[rust-std-snapshot-x86_64.sha256sum] = "f1eb68db2b28a56ed8701edba7cf3688011d903ca12ff9d85bd21d3f8f614792"
SRC_URI[rustc-snapshot-x86_64.sha256sum] = "9bebd360bcd9b5bb58f2a02930b9db4ae291adef259c96377f1f4cbd240bcf86"
SRC_URI[cargo-snapshot-x86_64.sha256sum] = "3cb2c68e987e5681fca9c930973f408a71151b1b255e69669a08e54d446ee803"
