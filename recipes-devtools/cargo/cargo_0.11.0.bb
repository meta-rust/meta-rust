require cargo-snapshot.inc
require cargo.inc

SRC_URI += " \
	git://github.com/rust-lang/cargo.git;protocol=https;name=cargo \
	file://0001-disable-cargo-snapshot-fetch.patch \
	file://0001-Never-update-the-registry-index.patch \
	git://github.com/rust-lang/rust-installer.git;protocol=https;name=rust-installer;destsuffix=${S}/src/rust-installer \
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
