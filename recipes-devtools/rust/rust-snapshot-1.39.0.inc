require rust-snapshot.inc

## This is information on the rust-snapshot (binary) used to build our current release.
## snapshot info is taken from rust/src/stage0.txt
## TODO: find a way to add additional SRC_URIs based on the contents of an
##       earlier SRC_URI.
RS_VERSION = "1.38.0"
CARGO_VERSION = "0.39.0"

# TODO: Add hashes for other architecture toolchains as well. Make a script?
SRC_URI[rustc-snapshot-x86_64.md5sum] = "53278262a3996982cd68730db7cb1efd"
SRC_URI[rustc-snapshot-x86_64.sha256sum] = "0fedde3406cf3367ceb00f493698e6bfc3264bd7f7253c85de7a042b45f873fa"
SRC_URI[rust-std-snapshot-x86_64.md5sum] = "0d32b76359613f73671acd13ea57b7ea"
SRC_URI[rust-std-snapshot-x86_64.sha256sum] = "51b334337804baeff7524e5496d396f254894d7529860d236975e9ed8fcca371"
SRC_URI[cargo-snapshot-x86_64.md5sum] = "7274cfe12905fe8ea6edbe131d3f6637"
SRC_URI[cargo-snapshot-x86_64.sha256sum] = "80bcb1368ce98d13cb371df89cbbed9007fb98843f34d07f2abd2c03b8f2747a"
