CARGO_SNAPSHOT = "cargo-0.24.0-${RUST_BUILD_SYS}"

SRC_URI[cargo-snapshot.md5sum] = "830041cfc8627d3f7187954993449cf9"
SRC_URI[cargo-snapshot.sha256sum] = "ff8a454104aba20426ea898ed7515ec5da7de07d11733cdda17462455beb76e8"

SRC_URI += "\
    https://static.rust-lang.org/dist/${CARGO_SNAPSHOT}.tar.gz;name=cargo-snapshot \
"

# When building cargo-native we don't have a built cargo to use so we must use
# the snapshot to bootstrap the build of cargo
CARGO_class-native = "${WORKDIR}/${CARGO_SNAPSHOT}/cargo/bin/cargo"
