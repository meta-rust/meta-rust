require rust-snapshot.inc

## This is information on the rust-snapshot (binary) used to build our current release.
## snapshot info is taken from rust/src/stage0.txt
## TODO: find a way to add additional SRC_URIs based on the contents of an
##       earlier SRC_URI.
RS_VERSION = "1.45.2"
CARGO_VERSION = "0.46.1"

# TODO: Add hashes for other architecture toolchains as well. Make a script?
SRC_URI[rust-std-snapshot-x86_64.sha256sum] = "02309322467af8e37256ccf1f064f5233c7fca4423dffde0bd5eb32cde46942a"
SRC_URI[rustc-snapshot-x86_64.sha256sum] = "0be5c8506fd9317c7d0dc8044b5fef8501caa74f88a9a22be795d68362dc57f6"
SRC_URI[cargo-snapshot-x86_64.sha256sum] = "a27eb5d47b520ef2c554605bf789f80652af63531b4f6a1195d61b3dfd0f6e9c"
