CARGO_SNAPSHOT = "cargo-0.21.0-${RUST_BUILD_SYS}"
SRC_URI[cargo-snapshot.md5sum] = "0e5389d2e38a14933dda77db8172cb1f"
SRC_URI[cargo-snapshot.sha256sum] = "caccf4ab039c806a9e6fdc7fe389cc88fb771e28e30d93c07a5c56ef845cdf57"

SRC_URI += "\
	https://static.rust-lang.org/dist/${CARGO_SNAPSHOT}.tar.gz;name=cargo-snapshot \
"

# When building cargo-native we don't have a built cargo to use so we must use
# the snapshot to bootstrap the build of cargo
CARGO_class-native = "${WORKDIR}/${CARGO_SNAPSHOT}/cargo/bin/cargo"
