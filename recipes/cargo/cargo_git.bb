SRCREV_cargo = "0f6667ca0631fe72d1e15759c845f0197e3dfe19"
require cargo.inc

SRC_URI += " \
	file://0001-custom_build-build-output-goes-in-the-directory-for-.patch \
\
	git://github.com/carllerche/curl-rust.git;protocol=https;name=curl-rust;destsuffix=curl-rust \
	file://curl-rust/0001-curl-sys-avoid-explicitly-linking-in-openssl.-If-it-.patch;patchdir=../curl-rust \
	file://curl-rust/0002-openssl-sys-is-used-in-curl-rust-so-include-it-expli.patch;patchdir=../curl-rust \
\
	git://github.com/alexcrichton/ssh2-rs.git;protocol=https;name=ssh2-rs;destsuffix=ssh2-rs \
	file://ssh2-rs/0001-Unconditionally-depend-on-openssl-sys.patch;patchdir=../ssh2-rs \
"

SRCREV_curl-rust = "6f007b4967ec12e36937dcb081abe0bdb3bcc508"
SRCREV_ssh2-rs = "982dc47a45a5a2d66ea092ee6bb9503ddcbf36d9"
SRCREV_FORMAT = "cargo_curl-rust_ssh2-rs"
EXTRA_OECARGO_PATHS = "\
	${WORKDIR}/curl-rust \
	${WORKDIR}/ssh2-rs \
"
