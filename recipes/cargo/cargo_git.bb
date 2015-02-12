# 2015-2-12
SRCREV_cargo = "0b84923203dce67ff8cf051728b6908c9c2e303c"

require cargo.inc

SRC_URI += " \
	git://github.com/carllerche/curl-rust.git;protocol=https;name=curl-rust;destsuffix=curl-rust \
	file://curl-rust/0001-curl-sys-avoid-explicitly-linking-in-openssl.-If-it-.patch;patchdir=../curl-rust \
	file://curl-rust/0002-openssl-sys-is-used-in-curl-rust-so-include-it-expli.patch;patchdir=../curl-rust \
\
	git://github.com/alexcrichton/ssh2-rs.git;protocol=https;name=ssh2-rs;destsuffix=ssh2-rs \
	file://ssh2-rs/0001-Unconditionally-depend-on-openssl-sys.patch;patchdir=../ssh2-rs \
"

# 0.1.14
SRCREV_curl-rust = "9181ea8f4ea2c7eb60224b5ebf464751165e2881"

# libssh2-sys 0.1.5 +2015-2-10
SRCREV_ssh2-rs = "8baa8ccb39cd1a43362d2a1ee87d8c3b91496cd7"
SRCREV_FORMAT = "cargo_curl-rust_ssh2-rs"
EXTRA_OECARGO_PATHS = "\
	${WORKDIR}/curl-rust \
	${WORKDIR}/ssh2-rs \
"
