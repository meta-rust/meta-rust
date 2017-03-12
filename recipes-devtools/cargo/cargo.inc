inherit cargo

SUMMARY = "Cargo downloads your Rust project's dependencies and builds your project"
HOMEPAGE = "http://crates.io"
SECTION = "devel"
LICENSE = "MIT | Apache-2.0"

DEPENDS = "openssl zlib libgit2 curl ca-certificates libssh2"

# Used in libgit2-sys's build.rs, needed for pkg-config to be used
export LIBGIT2_SYS_USE_PKG_CONFIG = "1"

BBCLASSEXTEND = "native"
