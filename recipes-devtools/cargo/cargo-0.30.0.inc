CARGO_SNAPSHOT = "cargo-0.29.0-${BUILD_ARCH}-unknown-linux-gnu"

SRC_URI[cargo-snapshot-x86_64.md5sum] = "f9d283378b9b0d8457f737c2a6bfbc67"
SRC_URI[cargo-snapshot-x86_64.sha256sum] = "a5e7749767c47669ed9b6e32c6fb8eda6b0fe1c63ac73a6d4666b5c1352bad24"


SRC_URI += "\
    https://static.rust-lang.org/dist/${CARGO_SNAPSHOT}.tar.gz;name=cargo-snapshot-${BUILD_ARCH} \
"

# When building cargo-native we don't have a built cargo to use so we must use
# the snapshot to bootstrap the build of cargo
CARGO_class-native = "${WORKDIR}/${CARGO_SNAPSHOT}/cargo/bin/cargo"
