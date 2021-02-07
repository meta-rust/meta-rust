require rust-snapshot.inc

## This is information on the rust-snapshot (binary) used to build our current release.
## snapshot info is taken from rust/src/stage0.txt
## TODO: find a way to add additional SRC_URIs based on the contents of an
##       earlier SRC_URI.
RS_VERSION = "1.33.0"
CARGO_VERSION = "0.34.0"

# TODO: Add hashes for other architecture toolchains as well. Make a script?
SRC_URI[rustc-snapshot-x86_64.sha256sum] = "57c5ced1a826d34f26e50adf041528dd0000f2a59e8be32d2359386843382ce1"
SRC_URI[rust-std-snapshot-x86_64.sha256sum] = "6f20343ed73faf5fdfc423bec38a9bb1910a0a962af6f2dddd7184407543ed0e"
SRC_URI[cargo-snapshot-x86_64.sha256sum] = "1730c8ebcacc1327eb28b328cb9f5a2c612bb3d9efff9c350647adf19f304e15"
