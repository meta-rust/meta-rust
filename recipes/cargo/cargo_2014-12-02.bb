SRCREV_cargo = "5a80c023690bc6171eccadcc49075d1b3edec8ce"
require cargo.inc

SRC_URI += " \
	file://0001-Update-for-nightly.patch \
	file://0001-custom_build-map-the-CFLAGS-and-CC-variables-for-HOS.patch \
\
	git://github.com/carllerche/curl-rust.git;protocol=https;name=curl-rust;destsuffix=curl-rust \
	file://curl-rust/0001-curl-sys-avoid-explicitly-linking-in-openssl-If-it-.patch;patchdir=../curl-rust \
	file://curl-rust/0001-openssl-sys-is-used-in-curl-rust-so-include-it-expli.patch;patchdir=../curl-rust \
\
	git://github.com/alexcrichton/ssh2-rs.git;protocol=https;name=ssh2-rs;destsuffix=ssh2-rs \
	file://ssh2-rs/0001-Unconditionally-depend-on-openssl-sys.patch;patchdir=../ssh2-rs \
"

SRCREV_curl-rust = "5d0f5c8848e3cf1e12480a1923ae888e24d58f63"
SRCREV_ssh2-rs = "490f91fb9e90bf4e305f1a23a051228c59e60eaf"
SRCREV_FORMAT = "cargo_curl-rust_ssh2-rs"
EXTRA_OECARGO_PATHS = "\
	${WORKDIR}/curl-rust \
	${WORKDIR}/ssh2-rs \
"
