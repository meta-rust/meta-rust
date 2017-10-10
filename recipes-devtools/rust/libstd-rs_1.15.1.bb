require rust-source-${PV}.inc
require libstd-rs.inc

LIC_FILES_CHKSUM = "file://../../COPYRIGHT;md5=43e1f1fb9c0ee3af66693d8c4fecafa8"

# Don't use jemalloc as it doesn't work for many targets.
# https://github.com/rust-lang/rust/pull/37392
CARGO_BUILD_FLAGS += "--features 'panic-unwind'"

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
