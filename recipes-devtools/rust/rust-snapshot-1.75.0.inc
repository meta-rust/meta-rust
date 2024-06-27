## This is information on the rust-snapshot (binary) used to build our current release.
## snapshot info is taken from rust/src/stage0.json
## Rust is self-hosting and bootstraps itself with a pre-built previous version of itself.
## The exact (previous) version that has been used is specified in the source tarball.
## The version is replicated here.
## TODO: find a way to add additional SRC_URIs based on the contents of an
##       earlier SRC_URI.

SNAPSHOT_VERSION = "1.74.0"

# TODO: Add hashes for other architecture toolchains as well.

# You can use scripts/rust-get-stage0.sh to update hashes
SRC_URI[rust-std-snapshot-x86_64.sha256sum] = "548413213012e2f62b08ed8a913a51210ae7402619027224580176031f2789ea"
SRC_URI[rustc-snapshot-x86_64.sha256sum]    = "7d464be2ae0d6ce69f056d1ea9a8ce2b3b1d537418caea216fdd303903972181"
SRC_URI[cargo-snapshot-x86_64.sha256sum]    = "f219386d4569c40b660518e99267afff428c13bf980bda7a614c8d4038d013f6"

SRC_URI[rust-std-snapshot-aarch64.sha256sum] = "c5ad01692bc08ce6f4db2ac815be63498b45013380c71f22b3d33bf3be767270"
SRC_URI[rustc-snapshot-aarch64.sha256sum]    = "a49bb365481913ead305658e7e9dc621da7895036b840fb57b1bc85c721d07e6"
SRC_URI[cargo-snapshot-aarch64.sha256sum]    = "a18dc9132cf76ccba90bcbb53b56a4d37ebfb34845f61e79f7b5d4710a269647"

SRC_URI[rust-std-snapshot-powerpc64le.sha256sum] = "785956d68855de18546c87d6d06cd2505cb8a10edba84327bf2b448420a31d55"
SRC_URI[rustc-snapshot-powerpc64le.sha256sum]    = "8727b1a92e88ac1ce05198ee185dac86553edd7f50b726781c9ab64544b59809"
SRC_URI[cargo-snapshot-powerpc64le.sha256sum]    = "2eccd404aabe5137a8e45b6173c27d08862a0e674d5866be71aff1434f271d50"

SRC_URI += " \
    https://static.rust-lang.org/dist/${RUST_STD_SNAPSHOT}.tar.xz;name=rust-std-snapshot-${RUST_BUILD_ARCH};subdir=rust-snapshot-components \
    https://static.rust-lang.org/dist/${RUSTC_SNAPSHOT}.tar.xz;name=rustc-snapshot-${RUST_BUILD_ARCH};subdir=rust-snapshot-components \
    https://static.rust-lang.org/dist/${CARGO_SNAPSHOT}.tar.xz;name=cargo-snapshot-${RUST_BUILD_ARCH};subdir=rust-snapshot-components \
"

RUST_STD_SNAPSHOT = "rust-std-${SNAPSHOT_VERSION}-${RUST_BUILD_ARCH}-unknown-linux-gnu"
RUSTC_SNAPSHOT = "rustc-${SNAPSHOT_VERSION}-${RUST_BUILD_ARCH}-unknown-linux-gnu"
CARGO_SNAPSHOT = "cargo-${SNAPSHOT_VERSION}-${RUST_BUILD_ARCH}-unknown-linux-gnu"
