SRCREV_cargo = "da789a6b4b4cd85aee65ed8f7e99e65de7a3d200"
require cargo.inc

SRC_URI += " \
	file://0001-Update-to-work-with-new-curl-rust.patch \	
\
	git://github.com/carllerche/curl-rust.git;protocol=https;name=curl-rust;destsuffix=curl-rust \
	file://curl-rust/0001-curl-sys-avoid-explicitly-linking-in-openssl-If-it-.patch;patchdir=../curl-rust \
	file://curl-rust/0001-openssl-sys-is-used-in-curl-rust-so-include-it-expli.patch;patchdir=../curl-rust \
\
	git://github.com/alexcrichton/gcc-rs.git;protocol=https;name=gcc-rs;destsuffix=gcc-rs \
\
	git://github.com/alexcrichton/ssh2-rs.git;protocol=https;name=ssh2-rs;destsuffix=ssh2-rs \
	file://ssh2-rs/0001-Unconditionally-depend-on-openssl-sys.patch;patchdir=../ssh2-rs \
	file://ssh2-rs/0001-Update-to-namespaced-io-FileType.patch;patchdir=../ssh2-rs \
	git://github.com/alexcrichton/tar-rs.git;protocol=https;name=tar-rs;destsuffix=tar-rs \
	file://tar-rs/0001-update-to-new-io-FileType-enum.patch;patchdir=../tar-rs \
	git://github.com/sfackler/rust-openssl.git;protocol=https;name=rust-openssl;destsuffix=rust-openssl \
	git://github.com/alexcrichton/git2-rs.git;protocol=https;name=git2-rs;destsuffix=git2-rs \
"
#file://gcc-rs/0001-XXX-hacks.patch;patchdir=../gcc-rs

SRCREV_curl-rust = "5d0f5c8848e3cf1e12480a1923ae888e24d58f63"
SRCREV_gcc-rs = "903e8f8a2e3766ad3d514404d452dbaa1d3b2d79"
SRCREV_ssh2-rs = "922531da4c22abe7a216672314315d41769d7fb1"
SRCREV_tar-rs = "2f3fb3a976d7fae105e3c97c8206266e763061ef"
SRCREV_rust-openssl = "fd680e8a336f8870a411a3047c45b47ee72beb37"
SRCREV_git2-rs = "d0d21ca14b4a410806b577b04c2d29f7f8e45f61"
SRCREV_FORMAT = "cargo_curl-rust_gcc-rs_ssh2-rs_tar-rs_rust-openssl_git2-rs"
EXTRA_OECARGO_PATHS = "\
	${WORKDIR}/tar-rs \
	${WORKDIR}/ssh2-rs \
	${WORKDIR}/rust-openssl \
	${WORKDIR}/curl-rust \
	${WORKDIR}/gcc-rs \
"

DEFAULT_PREFERENCE = "-1"
