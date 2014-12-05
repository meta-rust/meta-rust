SRCREV_cargo = "70f5205dba9887d8dab07f72dbc507aa74b12c1f"
require cargo.inc

SRC_URI += " \
	file://0001-custom_build-build-output-goes-in-the-directory-for-.patch \
\
	git://github.com/carllerche/curl-rust.git;protocol=https;name=curl-rust;destsuffix=curl-rust \
	file://curl-rust/0001-curl-sys-avoid-explicitly-linking-in-openssl-If-it-.patch;patchdir=../curl-rust \
	file://curl-rust/0001-openssl-sys-is-used-in-curl-rust-so-include-it-expli.patch;patchdir=../curl-rust \
\
	git://github.com/alexcrichton/ssh2-rs.git;protocol=https;name=ssh2-rs;destsuffix=ssh2-rs \
	file://ssh2-rs/0001-Unconditionally-depend-on-openssl-sys.patch;patchdir=../ssh2-rs \
\
	git://github.com/alexcrichton/gcc-rs.git;protocol=https;name=gcc-rs;destsuffix=gcc-rs \
	file://gcc-rs/0001-Support-use-of-namespaced-environment-variables-base.patch;patchdir=../gcc-rs \
"

SRCREV_curl-rust = "5d0f5c8848e3cf1e12480a1923ae888e24d58f63"
SRCREV_ssh2-rs = "490f91fb9e90bf4e305f1a23a051228c59e60eaf"
SRCREV_gcc-rs = "d32b24466d3e0094cef1c1809a04d7a28536f0e0"
SRCREV_FORMAT = "cargo_curl-rust_ssh2-rs_gcc-rs"
EXTRA_OECARGO_PATHS = "\
	${WORKDIR}/curl-rust \
	${WORKDIR}/ssh2-rs \
	${WORKDIR}/gcc-rs \
"
