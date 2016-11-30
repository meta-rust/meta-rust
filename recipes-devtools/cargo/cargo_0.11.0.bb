require cargo-snapshot.inc
require cargo.inc

SRC_URI += " \
	git://github.com/rust-lang/cargo.git;protocol=https;name=cargo \
	file://0001-disable-cargo-snapshot-fetch.patch \
	file://0001-Never-update-the-registry-index.patch \
	git://github.com/rust-lang/rust-installer.git;protocol=https;name=rust-installer;destsuffix=${S}/src/rust-installer \
	crate://crates.io/advapi32-sys/0.1.2 \
	crate://crates.io/bufstream/0.1.1 \
	crate://crates.io/crossbeam/0.2.8 \
	crate://crates.io/docopt/0.6.78 \
	crate://crates.io/env_logger/0.3.2 \
	crate://crates.io/filetime/0.1.10 \
	crate://crates.io/flate2/0.2.13 \
	crate://crates.io/fs2/0.2.3 \
	crate://crates.io/glob/0.2.11 \
	crate://crates.io/hamcrest/0.1.0 \
	crate://crates.io/kernel32-sys/0.2.1 \
	crate://crates.io/libc/0.2.8 \
	crate://crates.io/log/0.3.5 \
	crate://crates.io/num_cpus/0.2.11 \
	crate://crates.io/regex/0.1.58 \
	crate://crates.io/rustc-serialize/0.3.18 \
	crate://crates.io/tar/0.4.5 \
	crate://crates.io/tempdir/0.3.4 \
	crate://crates.io/term/0.4.4 \
	crate://crates.io/toml/0.1.28 \
	crate://crates.io/url/1.1.0 \
	crate://crates.io/winapi/0.2.6 \
	crate://crates.io/semver/0.2.3 \
	crate://crates.io/regex-syntax/0.3.0 \
	crate://crates.io/utf8-ranges/0.1.3 \
	crate://crates.io/gcc/0.3.26 \
	crate://crates.io/unicode-normalization/0.1.2 \
	crate://crates.io/libz-sys/1.0.2 \
	crate://crates.io/rand/0.3.14 \
	crate://crates.io/user32-sys/0.1.2 \
	crate://crates.io/idna/0.1.0 \
	crate://crates.io/strsim/0.3.0 \
	crate://crates.io/matches/0.1.2 \
	crate://crates.io/cmake/0.1.16 \
	crate://crates.io/gdi32-sys/0.1.1 \
	crate://crates.io/bitflags/0.1.1 \
	crate://crates.io/unicode-bidi/0.2.3 \
	crate://crates.io/pkg-config/0.3.8 \
	crate://crates.io/winapi-build/0.1.1 \
	crate://crates.io/memchr/0.1.10 \
	crate://crates.io/pnacl-build-helper/1.4.10 \
	crate://crates.io/nom/1.2.2 \
	crate://crates.io/num/0.1.31 \
	crate://crates.io/uuid/0.2.3 \
	crate://crates.io/aho-corasick/0.5.1 \
	crate://crates.io/libressl-pnacl-sys/2.1.6 \
	crate://crates.io/miniz-sys/0.1.7 \
	crate://crates.io/openssl-sys/0.7.8 \
	crate://crates.io/url/0.5.10 \
"
# Compatible with Rust 1.10.0
# https://static.rust-lang.org/dist/channel-rust-1.10.0.toml
SRCREV_cargo = "259324cd8f9bb6e1068a3a2b77685e90fda3e3b6"

SRCREV_rust-installer = "c37d3747da75c280237dc2d6b925078e69555499"

S = "${WORKDIR}/git"

LIC_FILES_CHKSUM ="\
	file://LICENSE-MIT;md5=362255802eb5aa87810d12ddf3cfedb4 \
	file://LICENSE-APACHE;md5=1836efb2eb779966696f473ee8540542 \
	file://LICENSE-THIRD-PARTY;md5=892ea68b169e69cfe75097fc38a15b56 \
"

## curl-rust
SRC_URI += "\
       git://github.com/carllerche/curl-rust.git;protocol=https;destsuffix=curl-rust;name=curl-rust \
       file://curl-rust/0001-curl-sys-avoid-explicitly-linking-in-openssl.patch;patchdir=../curl-rust \
       file://curl-rust/0002-remove-per-triple-deps-on-openssl-sys.patch;patchdir=../curl-rust \
"

# 0.2.19  / -sys 0.1.34
SRCREV_curl-rust = "45b8cb56fbed45f828f96bdd8c286b2b3a8a26cb"

SRCREV_FORMAT .= "_curl-rust"
EXTRA_OECARGO_PATHS += "${WORKDIR}/curl-rust"

## ssh2-rs
SRC_URI += "\
	git://github.com/alexcrichton/ssh2-rs.git;protocol=https;name=ssh2-rs;destsuffix=ssh2-rs \
	file://ssh2-rs/0001-libssh2-sys-avoid-explicitly-linking-in-openssl.patch;patchdir=../ssh2-rs \
"

# 0.2.11 / -sys 0.1.37
SRCREV_ssh2-rs = "ced77751cb780d0725a3411bd588c5a26ea79953"

SRCREV_FORMAT .= "_ssh2-rs"
EXTRA_OECARGO_PATHS += "${WORKDIR}/ssh2-rs"

## git2-rs
SRC_URI += "\
	git://github.com/alexcrichton/git2-rs.git;protocol=https;name=git2-rs;destsuffix=git2-rs \
	file://git2-rs/0001-libgit2-sys-avoid-blessed-triples.patch;patchdir=../git2-rs \
"

# 0.4.3 / -sys 0.4.2
SRCREV_git2-rs = "cd14fc7801e70d3b26a4e7e5d94785af1f7e9e58"

SRCREV_FORMAT .= "_git2-rs"
EXTRA_OECARGO_PATHS += "${WORKDIR}/git2-rs"
