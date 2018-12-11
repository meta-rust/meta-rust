CARGO_SNAPSHOT = "cargo-0.31.0-${BUILD_ARCH}-unknown-linux-gnu"

SRC_URI[cargo-snapshot-x86_64.md5sum] = "bad665c07e73a3f3cfa7ec3b209737fc"
SRC_URI[cargo-snapshot-x86_64.sha256sum] = "bfbabba9a2c1717fe1ce68469ce2de7b4b94e44e6a165d50b77de7bf7515bdb6"

SRC_URI += "\
    https://static.rust-lang.org/dist/${CARGO_SNAPSHOT}.tar.gz;name=cargo-snapshot-${BUILD_ARCH} \
"

# When building cargo-native we don't have a built cargo to use so we must use
# the snapshot to bootstrap the build of cargo
CARGO_class-native = "${WORKDIR}/${CARGO_SNAPSHOT}/cargo/bin/cargo"
