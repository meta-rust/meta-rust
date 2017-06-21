require cargo-snapshot-${PV}.inc
require cargo.inc

# cargo is not available when building cargo-native, so we must
# use a snapshot.
CARGO_class-native = "${WORKDIR}/cargo-${PV}-${RUST_BUILD_SYS}/cargo/bin/cargo"

SRC_URI += "git://github.com/rust-lang/cargo.git;protocol=https;branch=rust-1.18.0"
SRCREV = "${PV}"
S = "${WORKDIR}/git"

SRC_URI += " \
crate://crates.io/advapi32-sys/0.2.0 \
crate://crates.io/aho-corasick/0.5.3 \
crate://crates.io/aho-corasick/0.6.3 \
crate://crates.io/bitflags/0.7.0 \
crate://crates.io/bufstream/0.1.2 \
crate://crates.io/cfg-if/0.1.0 \
crate://crates.io/chrono/0.2.25 \
crate://crates.io/cmake/0.1.22 \
crate://crates.io/crossbeam/0.2.10 \
crate://crates.io/curl-sys/0.3.10 \
crate://crates.io/curl/0.4.6 \
crate://crates.io/docopt/0.7.0 \
crate://crates.io/dtoa/0.4.1 \
crate://crates.io/env_logger/0.4.2 \
crate://crates.io/filetime/0.1.10 \
crate://crates.io/flate2/0.2.17 \
crate://crates.io/foreign-types/0.2.0 \
crate://crates.io/fs2/0.4.1 \
crate://crates.io/gcc/0.3.45 \
crate://crates.io/gdi32-sys/0.2.0 \
crate://crates.io/git2-curl/0.7.0 \
crate://crates.io/git2/0.6.4 \
crate://crates.io/glob/0.2.11 \
crate://crates.io/hamcrest/0.1.1 \
crate://crates.io/idna/0.1.0 \
crate://crates.io/itoa/0.3.1 \
crate://crates.io/kernel32-sys/0.2.2 \
crate://crates.io/lazy_static/0.2.5 \
crate://crates.io/libc/0.2.21 \
crate://crates.io/libgit2-sys/0.6.7 \
crate://crates.io/libssh2-sys/0.2.5 \
crate://crates.io/libz-sys/1.0.13 \
crate://crates.io/log/0.3.7 \
crate://crates.io/matches/0.1.4 \
crate://crates.io/memchr/0.1.11 \
crate://crates.io/memchr/1.0.1 \
crate://crates.io/miniz-sys/0.1.9 \
crate://crates.io/miow/0.2.1 \
crate://crates.io/net2/0.2.27 \
crate://crates.io/num-bigint/0.1.37 \
crate://crates.io/num-complex/0.1.36 \
crate://crates.io/num-integer/0.1.33 \
crate://crates.io/num-iter/0.1.33 \
crate://crates.io/num-rational/0.1.36 \
crate://crates.io/num-traits/0.1.37 \
crate://crates.io/num/0.1.37 \
crate://crates.io/num_cpus/1.3.0 \
crate://crates.io/openssl-probe/0.1.1 \
crate://crates.io/openssl-sys/0.9.10 \
crate://crates.io/openssl/0.9.10 \
crate://crates.io/pkg-config/0.3.9 \
crate://crates.io/psapi-sys/0.1.0 \
crate://crates.io/quote/0.3.15 \
crate://crates.io/rand/0.3.15 \
crate://crates.io/redox_syscall/0.1.17 \
crate://crates.io/regex-syntax/0.3.9 \
crate://crates.io/regex-syntax/0.4.0 \
crate://crates.io/regex/0.1.80 \
crate://crates.io/regex/0.2.1 \
crate://crates.io/rustc-serialize/0.3.23 \
crate://crates.io/semver-parser/0.7.0 \
crate://crates.io/semver/0.6.0 \
crate://crates.io/serde/0.9.12 \
crate://crates.io/serde_codegen_internals/0.14.2 \
crate://crates.io/serde_derive/0.9.12 \
crate://crates.io/serde_ignored/0.0.2 \
crate://crates.io/serde_json/0.9.9 \
crate://crates.io/shell-escape/0.1.3 \
crate://crates.io/strsim/0.6.0 \
crate://crates.io/syn/0.11.9 \
crate://crates.io/synom/0.11.3 \
crate://crates.io/tar/0.4.10 \
crate://crates.io/tempdir/0.3.5 \
crate://crates.io/term/0.4.5 \
crate://crates.io/thread-id/2.0.0 \
crate://crates.io/thread-id/3.0.0 \
crate://crates.io/thread_local/0.2.7 \
crate://crates.io/thread_local/0.3.3 \
crate://crates.io/time/0.1.36 \
crate://crates.io/toml/0.3.2 \
crate://crates.io/unicode-bidi/0.2.5 \
crate://crates.io/unicode-normalization/0.1.4 \
crate://crates.io/unicode-xid/0.0.4 \
crate://crates.io/unreachable/0.1.1 \
crate://crates.io/url/1.4.0 \
crate://crates.io/user32-sys/0.2.0 \
crate://crates.io/utf8-ranges/0.1.3 \
crate://crates.io/utf8-ranges/1.0.0 \
crate://crates.io/void/1.0.2 \
crate://crates.io/winapi-build/0.1.1 \
crate://crates.io/winapi/0.2.8 \
crate://crates.io/ws2_32-sys/0.2.1 \
"

LIC_FILES_CHKSUM=" \
    file://LICENSE-MIT;md5=362255802eb5aa87810d12ddf3cfedb4 \
    file://LICENSE-APACHE;md5=1836efb2eb779966696f473ee8540542 \
    file://LICENSE-THIRD-PARTY;md5=892ea68b169e69cfe75097fc38a15b56 \
"
