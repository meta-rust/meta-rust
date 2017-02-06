# Specifics for Rust 1.15.1

## This is information on the rust-snapshot (binary) used to build our current release.
## snapshot info is taken from rust/src/stage0.txt
## TODO: find a way to add additional SRC_URIs based on the contents of an
##       earlier SRC_URI.
RS_VERSION = "1.14.0"

RUST_SNAPSHOT = "rustc-${RS_VERSION}-${RUST_BUILD_SYS}"

# These are x86_64-unknown-linux-gnu hashes, how can we add more?
SRC_URI[rust-snapshot.md5sum] = "f178d9d6aad0f87c451f4b2f93170633"
SRC_URI[rust-snapshot.sha256sum] = "0eeec4211aa872f24c220200a0c2b095bbfc9c0f737c1c5df2555967c8f36787"

SRC_URI += "\
	https://static.rust-lang.org/dist/rustc-${PV}-src.tar.gz;name=rust \
    "
SRC_URI[rust.md5sum] = "5bbfff5ef8857a73d120616546a7fd29"
SRC_URI[rust.sha256sum] = "2e7daad418a830b45b977cd7ecf181b65f30f73df63ff36e124ea5fe5d1af327"

# later versions of rust change the directory that they unextract to
RUSTSRC = "${WORKDIR}/rustc-${PV}-src"
# set this as our default
S = "${RUSTSRC}"
