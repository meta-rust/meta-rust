CARGO_SNAPSHOT = "cargo-0.26.0-${RUST_BUILD_SYS}"

SRC_URI[cargo-snapshot.md5sum] = "b0de62d86f0ba71078471d09916873c6"
SRC_URI[cargo-snapshot.sha256sum] = "9ba227f2364f618dc9415dacf3a5dce17458e1cb9f6d4fe860416cb68db894e4"

SRC_URI += "\
    https://static.rust-lang.org/dist/${CARGO_SNAPSHOT}.tar.gz;name=cargo-snapshot \
"

# When building cargo-native we don't have a built cargo to use so we must use
# the snapshot to bootstrap the build of cargo
CARGO_class-native = "${WORKDIR}/${CARGO_SNAPSHOT}/cargo/bin/cargo"
