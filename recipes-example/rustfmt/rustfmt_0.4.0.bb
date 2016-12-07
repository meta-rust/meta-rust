inherit cargo

SRC_URI = " \
    crate://crates.io/aho-corasick/0.5.1 \
    crate://crates.io/bitflags/0.5.0 \
    crate://crates.io/diff/0.1.9 \
    crate://crates.io/env_logger/0.3.2 \
    crate://crates.io/getopts/0.2.14 \
    crate://crates.io/kernel32-sys/0.2.1 \
    crate://crates.io/libc/0.2.8 \
    crate://crates.io/log/0.3.5 \
    crate://crates.io/memchr/0.1.10 \
    crate://crates.io/regex/0.1.58 \
    crate://crates.io/regex-syntax/0.3.0 \
    crate://crates.io/rustc-serialize/0.3.18 \
    crate://crates.io/strings/0.0.1 \
    crate://crates.io/syntex_syntax/0.30.0 \
    crate://crates.io/term/0.2.14 \
    crate://crates.io/toml/0.1.28 \
    crate://crates.io/unicode-segmentation/0.1.2 \
    crate://crates.io/unicode-xid/0.0.3 \
    crate://crates.io/utf8-ranges/0.1.3 \
    crate://crates.io/winapi/0.2.6 \
    crate://crates.io/winapi-build/0.1.1 \
    crate://crates.io/rustfmt/0.4.0 \
"
# rustfmt 0.5.0
#LIC_FILES_CHKSUM=" \
#    file://LICENSE-APACHE;md5=1836efb2eb779966696f473ee8540542 \
#    file://LICENSE-MIT;md5=0b29d505d9225d1f0815cbdcf602b901 \
#"
LIC_FILES_CHKSUM="file://${COREBASE}/meta/COPYING.MIT;md5=3da9cfbcb788c80a0384361b4de20420"

SUMMARY = "Format Rust Code"
HOMEPAGE = "https://github.com/rust-lang-nursery/rustfmt"
LICENSE = "MIT | Apache-2.0"
