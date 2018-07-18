CARGO_SNAPSHOT = "cargo-0.27.0-${BUILD_ARCH}-unknown-linux-gnu"

SRC_URI[cargo-snapshot-x86_64.md5sum] = "ca366ba1e97ffc02b72dc74859db35e2"
SRC_URI[cargo-snapshot-x86_64.sha256sum] = "8c17710252513d8130141f2c12b4efeef67f0def252b94b246fe326a9a75043b"

SRC_URI += "\
    https://static.rust-lang.org/dist/${CARGO_SNAPSHOT}.tar.gz;name=cargo-snapshot-${BUILD_ARCH} \
"

# When building cargo-native we don't have a built cargo to use so we must use
# the snapshot to bootstrap the build of cargo
CARGO_class-native = "${WORKDIR}/${CARGO_SNAPSHOT}/cargo/bin/cargo"
