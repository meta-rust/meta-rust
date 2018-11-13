CARGO_SNAPSHOT = "cargo-0.30.0-${BUILD_ARCH}-unknown-linux-gnu"

SRC_URI[cargo-snapshot-x86_64.md5sum] = "79b62c75b11ef480163276be189fdac5"
SRC_URI[cargo-snapshot-x86_64.sha256sum] = "32f210fd3142fda7825a06e95d1aa4b54035c2da435d8cf0dd03fad410c8002f"

SRC_URI += "\
    https://static.rust-lang.org/dist/${CARGO_SNAPSHOT}.tar.gz;name=cargo-snapshot-${BUILD_ARCH} \
"

# When building cargo-native we don't have a built cargo to use so we must use
# the snapshot to bootstrap the build of cargo
CARGO_class-native = "${WORKDIR}/${CARGO_SNAPSHOT}/cargo/bin/cargo"
