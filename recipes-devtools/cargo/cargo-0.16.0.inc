CARGO_SNAPSHOT = "2016-09-01/cargo-nightly-x86_64-unknown-linux-gnu.tar.gz;downloadfilename=cargo-nightly-x86_64-unknown-linux-gnu-2016-09-01.tar.gz"
SRC_URI[cargo-snapshot.md5sum] = "d41ebf79290a7c9c9e5df87cb27e5091"
SRC_URI[cargo-snapshot.sha256sum] = "365e5cad79512d244b8ced32f8e5b86a710fc6c17f0d0f5f744b8058ef6dc756"

SRC_URI += "\
	https://static.rust-lang.org/cargo-dist/${CARGO_SNAPSHOT};name=cargo-snapshot \
"

# When building cargo-native we don't have a built cargo to use so we must use
# the snapshot to bootstrap the build of cargo
CARGO_class-native = "${WORKDIR}/cargo-nightly-${RUST_BUILD_SYS}/cargo/bin/cargo"
