inherit cargo


SRC_URI += " \
    crate://crates.io/aho-corasick/0.6.3 \
    crate://crates.io/bitflags/0.9.1 \
    crate://crates.io/diff/0.1.10 \
    crate://crates.io/dtoa/0.4.1 \
    crate://crates.io/env_logger/0.4.3 \
    crate://crates.io/extprim/1.2.2 \
    crate://crates.io/getopts/0.2.14 \
    crate://crates.io/itoa/0.3.1 \
    crate://crates.io/kernel32-sys/0.2.2 \
    crate://crates.io/libc/0.2.23 \
    crate://crates.io/log/0.3.8 \
    crate://crates.io/memchr/1.0.1 \
    crate://crates.io/num-traits/0.1.39 \
    crate://crates.io/quote/0.3.15 \
    crate://crates.io/rand/0.3.15 \
    crate://crates.io/regex-syntax/0.4.1 \
    crate://crates.io/regex/0.2.2 \
    crate://crates.io/rustc_version/0.2.1 \
    crate://crates.io/semver-parser/0.7.0 \
    crate://crates.io/semver/0.6.0 \
    crate://crates.io/serde/1.0.8 \
    crate://crates.io/serde_derive/1.0.8 \
    crate://crates.io/serde_derive_internals/0.15.1 \
    crate://crates.io/serde_json/1.0.2 \
    crate://crates.io/strings/0.1.0 \
    crate://crates.io/syn/0.11.11 \
    crate://crates.io/synom/0.11.3 \
    crate://crates.io/syntex_errors/0.59.0 \
    crate://crates.io/syntex_pos/0.59.0 \
    crate://crates.io/syntex_syntax/0.59.0 \
    crate://crates.io/term/0.4.5 \
    crate://crates.io/thread-id/3.1.0 \
    crate://crates.io/thread_local/0.3.3 \
    crate://crates.io/toml/0.4.1 \
    crate://crates.io/unicode-segmentation/1.2.0 \
    crate://crates.io/unicode-xid/0.0.4 \
    crate://crates.io/unicode-xid/0.1.0 \
    crate://crates.io/unreachable/0.1.1 \
    crate://crates.io/utf8-ranges/1.0.0 \
    crate://crates.io/void/1.0.2 \
    crate://crates.io/winapi-build/0.1.1 \
    crate://crates.io/winapi/0.2.8 \
    crate://crates.io/rustfmt/0.9.0 \
"

LIC_FILES_CHKSUM=" \
    file://LICENSE-APACHE;md5=1836efb2eb779966696f473ee8540542 \
    file://LICENSE-MIT;md5=0b29d505d9225d1f0815cbdcf602b901 \
"

SUMMARY = "Tool to find and fix Rust formatting issues"
HOMEPAGE = "https://github.com/rust-lang-nursery/rustfmt"
LICENSE = "Apache-2.0 | MIT"
