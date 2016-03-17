require cargo-snapshot.inc
require cargo.inc

SRC_URI += " \
	https://github.com/rust-lang/cargo/archive/${PV}.tar.gz;name=cargo \
	file://0001-disable-cargo-snapshot-fetch.patch \
	git://github.com/rust-lang/rust-installer.git;protocol=https;name=rust-installer;destsuffix=${BP}/src/rust-installer \
"
SRC_URI[cargo.md5sum] = "c3002e297f125ad40b2e0279219163bc"
SRC_URI[cargo.sha256sum] = "4cadc436be442505851f3a8e9ffff1ef10b6379101a7f8e0afa9fa80f5198f89"

SRCREV_rust-installer = "c37d3747da75c280237dc2d6b925078e69555499"

S = "${WORKDIR}/${BP}"

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

# 0.2.14  / -sys 0.1.29
SRCREV_curl-rust = "76172b3ebf958fcf0b10d400f19ee02486a80ee7"

SRCREV_FORMAT .= "_curl-rust"
EXTRA_OECARGO_PATHS += "${WORKDIR}/curl-rust"

## ssh2-rs
SRC_URI += "\
	git://github.com/alexcrichton/ssh2-rs.git;protocol=https;name=ssh2-rs;destsuffix=ssh2-rs \
	file://ssh2-rs/0001-libssh2-sys-avoid-explicitly-linking-in-openssl.patch;patchdir=../ssh2-rs \
"

# 0.2.10 / -sys 0.1.34
SRCREV_ssh2-rs = "00af6ead0c3d4b82e05bee4d9963ef3823bcf524"

SRCREV_FORMAT .= "_ssh2-rs"
EXTRA_OECARGO_PATHS += "${WORKDIR}/ssh2-rs"

## git2-rs
SRC_URI += "\
	git://github.com/alexcrichton/git2-rs.git;protocol=https;name=git2-rs;destsuffix=git2-rs \
	file://git2-rs/0001-libgit2-sys-avoid-blessed-triples.patch;patchdir=../git2-rs \
"

# 0.3.3 / -sys 0.3.8
SRCREV_git2-rs = "19b6873c1fad7dc93c9c2dac4cba339dacf16efa"

SRCREV_FORMAT .= "_git2-rs"
EXTRA_OECARGO_PATHS += "${WORKDIR}/git2-rs"
