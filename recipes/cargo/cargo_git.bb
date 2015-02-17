# 2015-2-12
SRCREV_cargo = "0b84923203dce67ff8cf051728b6908c9c2e303c"

require cargo.inc

SRC_URI += " \
	file:///0001-update-Rust.patch \
\
	git://github.com/carllerche/curl-rust.git;protocol=https;destsuffix=curl-rust;name=curl-rust \
	git://github.com/alexcrichton/curl.git;protocol=https;destsuffix=curl-rust/curl-sys/curl;name=curl;branch=configure \
	file://curl-rust/0001-curl-sys-avoid-explicitly-linking-in-openssl.-If-it-.patch;patchdir=../curl-rust \
	file://curl-rust/0002-openssl-sys-is-used-in-curl-rust-so-include-it-expli.patch;patchdir=../curl-rust \
	file://curl-rust/0003-remove-per-triple-deps-on-openssl-sys.patch;patchdir=../curl-rust \
\
	git://github.com/alexcrichton/ssh2-rs.git;protocol=https;name=ssh2-rs;destsuffix=ssh2-rs \
	file://ssh2-rs/0001-Unconditionally-depend-on-openssl-sys.patch;patchdir=../ssh2-rs \
	file://ssh2-rs/0002-libssh2-sys-only-support-pkg-config.patch;patchdir=../ssh2-rs \
\
	git://github.com/alexcrichton/git2-rs.git;protocol=https;name=git2-rs;destsuffix=git2-rs \
	file://git2-rs/0001-Add-generic-openssl-sys-dep.patch;patchdir=../git2-rs \
"

SRCREV_git2-rs = "d0d21ca14b4a410806b577b04c2d29f7f8e45f61"

# 0.1.14
SRCREV_curl-rust = "9181ea8f4ea2c7eb60224b5ebf464751165e2881"

# FIXME: we don't actually use this, and shouldn't need to fetch it, but not having it results in:
## target/snapshot/bin/cargo build --target x86_64-linux  --verbose 
## Failed to resolve path '/home/cody/obj/y/tmp/work/x86_64-linux/cargo-native/git+gitAUTOINC+0b84923203_9181ea8f4e_8baa8ccb39-r0/curl-rust/curl-sys/curl/.git': No such file or directory
SRCREV_curl = "ac30e9a7746c8641f4871e59b831ec28530c5c73"

# libssh2-sys 0.1.5 +2015-2-10
SRCREV_ssh2-rs = "8baa8ccb39cd1a43362d2a1ee87d8c3b91496cd7"
SRCREV_FORMAT = "cargo_curl-rust_curl_ssh2-rs_git2-rs"
EXTRA_OECARGO_PATHS = "\
	${WORKDIR}/curl-rust \
	${WORKDIR}/ssh2-rs \
	${WORKDIR}/git2-rs \
"
