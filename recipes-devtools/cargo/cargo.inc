require cargo-snapshot.inc

SECTION = "devel"

DEPENDS = "openssl zlib libgit2 curl ca-certificates libssh2"

SRC_URI += "\
	http://static-rust-lang-org.s3.amazonaws.com/cargo-dist/${CARGO_SNAPSHOT} \
"

LIC_FILES_CHKSUM += " \
file://LICENSE-APACHE;md5=1836efb2eb779966696f473ee8540542 \
file://LICENSE-THIRD-PARTY;md5=892ea68b169e69cfe75097fc38a15b56 \
"

# Used in libgit2-sys's build.rs, needed for pkg-config to be used
export LIBGIT2_SYS_USE_PKG_CONFIG = "1"

# When building cargo-native we don't have a built cargo to use so we must use
# the snapshot to bootstrap the build of cargo
CARGO_class-native = "${WORKDIR}/cargo-nightly-${RUST_BUILD_SYS}/cargo/bin/cargo"

BBCLASSEXTEND = "native"
