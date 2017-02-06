require rust-source-${PV}.inc
require libstd-rs.inc

EXTRA_OECONF = "--disable-rustbuild"

CARGO_BUILD_FLAGS += "--features 'jemalloc panic-unwind'"

SRC_URI += "\
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
