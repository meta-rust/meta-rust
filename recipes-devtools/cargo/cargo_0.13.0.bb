require cargo-snapshot.inc
require cargo.inc

SRC_URI += " \
	git://github.com/rust-lang/cargo.git;protocol=https;name=cargo \
	crate://crates.io/advapi32-sys/0.2.0 \
	crate://crates.io/aho-corasick/0.5.2 \
	crate://crates.io/bitflags/0.1.1 \
	crate://crates.io/bitflags/0.7.0 \
	crate://crates.io/bufstream/0.1.2 \
	crate://crates.io/cfg-if/0.1.0 \
	crate://crates.io/cmake/0.1.17 \
	crate://crates.io/crossbeam/0.2.9 \
	crate://crates.io/curl-sys/0.2.1 \
	crate://crates.io/curl/0.3.2 \
	crate://crates.io/docopt/0.6.82 \
	crate://crates.io/env_logger/0.3.4 \
	crate://crates.io/filetime/0.1.10 \
	crate://crates.io/flate2/0.2.14 \
	crate://crates.io/fs2/0.2.5 \
	crate://crates.io/gcc/0.3.32 \
	crate://crates.io/gdi32-sys/0.2.0 \
	crate://crates.io/git2-curl/0.5.0 \
	crate://crates.io/git2/0.4.4 \
	crate://crates.io/glob/0.2.11 \
	crate://crates.io/hamcrest/0.1.0 \
	crate://crates.io/idna/0.1.0 \
	crate://crates.io/kernel32-sys/0.2.2 \
	crate://crates.io/lazy_static/0.2.1 \
	crate://crates.io/libc/0.2.15 \
	crate://crates.io/libgit2-sys/0.4.5 \
	crate://crates.io/libressl-pnacl-sys/2.1.6 \
	crate://crates.io/libssh2-sys/0.1.38 \
	crate://crates.io/libz-sys/1.0.5 \
	crate://crates.io/log/0.3.6 \
	crate://crates.io/matches/0.1.2 \
	crate://crates.io/memchr/0.1.11 \
	crate://crates.io/miniz-sys/0.1.7 \
	crate://crates.io/miow/0.1.3 \
	crate://crates.io/net2/0.2.26 \
	crate://crates.io/nom/1.2.4 \
	crate://crates.io/num-bigint/0.1.33 \
	crate://crates.io/num-complex/0.1.33 \
	crate://crates.io/num-integer/0.1.32 \
	crate://crates.io/num-iter/0.1.32 \
	crate://crates.io/num-rational/0.1.32 \
	crate://crates.io/num-traits/0.1.34 \
	crate://crates.io/num/0.1.34 \
	crate://crates.io/num_cpus/1.0.0 \
	crate://crates.io/openssl-sys-extras/0.7.14 \
	crate://crates.io/openssl-sys/0.7.14 \
	crate://crates.io/openssl/0.7.14 \
	crate://crates.io/pkg-config/0.3.8 \
	crate://crates.io/pnacl-build-helper/1.4.10 \
	crate://crates.io/rand/0.3.14 \
	crate://crates.io/regex-syntax/0.3.4 \
	crate://crates.io/regex/0.1.73 \
	crate://crates.io/rustc-serialize/0.3.19 \
	crate://crates.io/semver/0.2.3 \
	crate://crates.io/strsim/0.3.0 \
	crate://crates.io/tar/0.4.8 \
	crate://crates.io/tempdir/0.3.5 \
	crate://crates.io/term/0.4.4 \
	crate://crates.io/thread-id/2.0.0 \
	crate://crates.io/thread_local/0.2.6 \
	crate://crates.io/toml/0.2.0 \
	crate://crates.io/unicode-bidi/0.2.3 \
	crate://crates.io/unicode-normalization/0.1.2 \
	crate://crates.io/url/1.2.0 \
	crate://crates.io/user32-sys/0.2.0 \
	crate://crates.io/utf8-ranges/0.1.3 \
	crate://crates.io/winapi-build/0.1.1 \
	crate://crates.io/winapi/0.2.8 \
	crate://crates.io/ws2_32-sys/0.2.1 \
"
# Compatible with Rust 1.12.1
# https://static.rust-lang.org/dist/channel-rust-1.12.1.toml
SRCREV_cargo = "109cb7c33d426044d141457049bd0fffaca1327c"

S = "${WORKDIR}/git"

LIC_FILES_CHKSUM ="\
	file://LICENSE-MIT;md5=362255802eb5aa87810d12ddf3cfedb4 \
	file://LICENSE-APACHE;md5=1836efb2eb779966696f473ee8540542 \
	file://LICENSE-THIRD-PARTY;md5=892ea68b169e69cfe75097fc38a15b56 \
"
