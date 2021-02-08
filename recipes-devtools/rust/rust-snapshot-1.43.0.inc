require rust-snapshot.inc

## This is information on the rust-snapshot (binary) used to build our current release.
## snapshot info is taken from rust/src/stage0.txt
## TODO: find a way to add additional SRC_URIs based on the contents of an
##       earlier SRC_URI.
RS_VERSION = "1.43.1"
CARGO_VERSION = "0.43.0"

# TODO: Add hashes for other architecture toolchains as well. Make a script?
SRC_URI[rustc-snapshot-x86_64.sha256sum] = "a18b89572ff2e55eb9e0428efcdb60eacd82fe28c4d825d169b0ffc9e3c55ceb"
SRC_URI[rust-std-snapshot-x86_64.sha256sum] = "dabc62db53c2e7ffeba2824d4c52a938486b04c01a93ecba00c5d529868f6cfc"
SRC_URI[cargo-snapshot-x86_64.sha256sum] = "fe7e40786f6e013d471f2f8ed51ba268611122065930a6d5a10bf20146997270"
