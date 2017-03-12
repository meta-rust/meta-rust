require rust-source-${PV}.inc
require libstd-rs.inc

# Don't use jemalloc as it doesn't work for many targets.
# https://github.com/rust-lang/rust/pull/37392 
CARGO_BUILD_FLAGS += "--features 'panic-unwind'"

SRC_URI += " \
	crate://crates.io/aho-corasick/0.6.3 \
	crate://crates.io/ansi_term/0.9.0 \
	crate://crates.io/atty/0.2.2 \
	crate://crates.io/bitflags/0.5.0 \
	crate://crates.io/bitflags/0.8.2 \
	crate://crates.io/clap/2.22.1 \
	crate://crates.io/cmake/0.1.22 \
	crate://crates.io/dtoa/0.4.1 \
	crate://crates.io/env_logger/0.4.2 \
	crate://crates.io/filetime/0.1.10 \
	crate://crates.io/gcc/0.3.45 \
	crate://crates.io/getopts/0.2.14 \
	crate://crates.io/handlebars/0.25.2 \
	crate://crates.io/itoa/0.3.1 \
	crate://crates.io/kernel32-sys/0.2.2 \
	crate://crates.io/lazy_static/0.2.5 \
	crate://crates.io/libc/0.2.21 \
	crate://crates.io/log/0.3.7 \
	crate://crates.io/mdbook/0.0.19 \
	crate://crates.io/memchr/1.0.1 \
	crate://crates.io/num-traits/0.1.37 \
	crate://crates.io/num_cpus/0.2.13 \
	crate://crates.io/open/1.2.0 \
	crate://crates.io/pest/0.3.3 \
	crate://crates.io/pulldown-cmark/0.0.14 \
	crate://crates.io/pulldown-cmark/0.0.8 \
	crate://crates.io/quick-error/1.1.0 \
	crate://crates.io/regex-syntax/0.4.0 \
	crate://crates.io/regex/0.2.1 \
	crate://crates.io/rls-data/0.1.0 \
	crate://crates.io/rls-span/0.1.0 \
	crate://crates.io/rustc-serialize/0.3.23 \
	crate://crates.io/serde/0.9.11 \
	crate://crates.io/serde_json/0.9.9 \
	crate://crates.io/strsim/0.6.0 \
	crate://crates.io/term_size/0.2.3 \
	crate://crates.io/thread-id/3.0.0 \
	crate://crates.io/thread_local/0.3.3 \
	crate://crates.io/toml/0.1.30 \
	crate://crates.io/toml/0.3.1 \
	crate://crates.io/unicode-segmentation/1.1.0 \
	crate://crates.io/unicode-width/0.1.4 \
	crate://crates.io/unreachable/0.1.1 \
	crate://crates.io/utf8-ranges/1.0.0 \
	crate://crates.io/vec_map/0.7.0 \
	crate://crates.io/void/1.0.2 \
	crate://crates.io/winapi-build/0.1.1 \
	crate://crates.io/winapi/0.2.8 \
"
