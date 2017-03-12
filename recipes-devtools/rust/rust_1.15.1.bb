require rust.inc
require rust-source-${PV}.inc
require rust-snapshot-${PV}.inc

SRC_URI += " \
        file://rust-${PV}/0003-std-thread_local-workaround-for-NULL-__dso_handle.patch \
        "

# These are extracted from rustc/src/bootstrap/Cargo.toml.
SRC_URI += " \
	crate://crates.io/cmake/0.1.18 \
	crate://crates.io/env_logger/0.3.5 \
	crate://crates.io/filetime/0.1.10 \
	crate://crates.io/gcc/0.3.40 \
	crate://crates.io/getopts/0.2.14 \
	crate://crates.io/libc/0.2.17 \
	crate://crates.io/log/0.3.6 \
	crate://crates.io/num_cpus/0.2.13 \
	crate://crates.io/rustc-serialize/0.3.19 \
	crate://crates.io/toml/0.1.30 \
"

DEPENDS += "rust-llvm (=${PV})"

# Otherwise we'll depend on what we provide
INHIBIT_DEFAULT_RUST_DEPS_class-native = "1"
# We don't need to depend on gcc-native because yocto assumes it exists
PROVIDES_class-native = "virtual/${TARGET_PREFIX}rust"

BBCLASSEXTEND = "native"
