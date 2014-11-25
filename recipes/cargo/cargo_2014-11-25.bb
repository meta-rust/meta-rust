SRCREV_cargo = "f936f3543fd1d4f2101cd937a4f52ce9f9676eae"
require cargo.inc

SRC_URI += " \
	git://github.com/carllerche/curl-rust.git;protocol=http;name=curl-rust;destsuffix=curl-rust \
	file://curl-rust/0001-curl-sys-avoid-explicitly-linking-in-openssl-If-it-.patch;patchdir=../curl-rust \
	file://curl-rust//0001-openssl-sys-is-used-in-curl-rust-so-include-it-expli.patch;patchdir=../curl-rust \
"

SRCREV_curl-rust = "c1b96e146f6752353a1e84cca932c628e6bf73af"
SRCREV_FORMAT = "cargo_curl-rust"
EXTRA_OECARGO_PATHS = "${WORKDIR}/curl-rust"

