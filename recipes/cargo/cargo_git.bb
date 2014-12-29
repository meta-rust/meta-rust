SRCREV_cargo = "b46015585bba8f4489f473e23df8ea4b8c66c8c0"
require cargo.inc

SRC_URI += " \
	git://github.com/carllerche/curl-rust.git;protocol=https;name=curl-rust;destsuffix=curl-rust \
	file://curl-rust/0001-curl-sys-avoid-explicitly-linking-in-openssl.-If-it-.patch;patchdir=../curl-rust \
	file://curl-rust/0002-openssl-sys-is-used-in-curl-rust-so-include-it-expli.patch;patchdir=../curl-rust \
\
	git://github.com/alexcrichton/ssh2-rs.git;protocol=https;name=ssh2-rs;destsuffix=ssh2-rs \
	file://ssh2-rs/0001-Unconditionally-depend-on-openssl-sys.patch;patchdir=../ssh2-rs \
"

SRCREV_curl-rust = "4517ee606c65bbe03e4ad4f661725eb80e667a69"
SRCREV_ssh2-rs = "509a8459e466ffa4705a0c686b80ac80b499f5d5"
SRCREV_FORMAT = "cargo_curl-rust_ssh2-rs"
EXTRA_OECARGO_PATHS = "\
	${WORKDIR}/curl-rust \
	${WORKDIR}/ssh2-rs \
"
