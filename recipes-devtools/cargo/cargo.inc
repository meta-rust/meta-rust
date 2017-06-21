inherit cargo
inherit patch

SUMMARY = "Cargo downloads your Rust project's dependencies and builds your project"
HOMEPAGE = "http://crates.io"
SECTION = "devel"
LICENSE = "MIT | Apache-2.0"

DEPENDS = "openssl zlib libgit2 curl ca-certificates libssh2"

SRC_URI = "\
	http://static-rust-lang-org.s3.amazonaws.com/cargo-dist/${CARGO_SNAPSHOT} \
"

# Used in libgit2-sys's build.rs, needed for pkg-config to be used
export LIBGIT2_SYS_USE_PKG_CONFIG = "1"

# When building cargo-native we don't have a built cargo to use so we must use
# the snapshot to bootstrap the build of cargo
CARGO_class-native = "${WORKDIR}/cargo-nightly-${RUST_BUILD_SYS}/cargo/bin/cargo"

BBCLASSEXTEND = "native"
