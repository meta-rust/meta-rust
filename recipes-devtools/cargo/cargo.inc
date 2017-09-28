SECTION = "devel"

DEPENDS = "openssl zlib libgit2 curl ca-certificates libssh2"

SRC_URI += "\
	https://static.rust-lang.org/cargo-dist/${CARGO_SNAPSHOT};name=cargo-snapshot \
"

LIC_FILES_CHKSUM += " \
file://LICENSE-THIRD-PARTY;md5=892ea68b169e69cfe75097fc38a15b56 \
"

# Used in libgit2-sys's build.rs, needed for pkg-config to be used
export LIBGIT2_SYS_USE_PKG_CONFIG = "1"

# When building cargo-native we don't have a built cargo to use so we must use
# the snapshot to bootstrap the build of cargo
CARGO_class-native = "${WORKDIR}/cargo-nightly-${RUST_BUILD_SYS}/cargo/bin/cargo"

BBCLASSEXTEND = "native"
