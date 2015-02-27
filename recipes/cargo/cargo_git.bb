# 2015-2-19
SRCREV_cargo = "43755c00e8a93a3478a1179bca98a7f8b56ecbca"

require cargo.inc

SRC_URI += " \
	git://github.com/carllerche/curl-rust.git;protocol=https;destsuffix=curl-rust;name=curl-rust \
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
\
\
	git://github.com/sfackler/rust-openssl.git;protocol=https;name=rust-openssl;destsuffix=rust-openssl \
\
\
	git://github.com/alexcrichton/curl.git;protocol=https;destsuffix=curl-rust/curl-sys/curl;name=curl;branch=configure \
	git://github.com/alexcrichton/libgit2.git;protocol=https;destsuffix=git2-rs/libgit2-sys/libgit2;name=libgit2;branch=libgit2-2014-12-19 \
"

# 0.1.17
SRCREV_curl-rust = "b7089a71fba5757e36f8cb1b3767183d4b79c20f"

# 0.1.11 / -sys 0.1.8
SRCREV_ssh2-rs = "c4c46c2d68dd207371c0565e2de2439bac583edc"

# 0.1.20
SRCREV_git2-rs = "4f2757055ecb3c52346d7163e321eb9d510f94ba"

## This is only included to avoid cargo spuriously complaining about us having
## 2 versions of openssl-sys linked in
# 0.4.3 +2015-02-22
SRCREV_rust-openssl = "ebd906293376ee8ed3b7ddafa4573d2a9222d8b7"
SRCREV_rustc-serialize = "213ef7b16e21a8b1a84e4d7c120e317ec0a66824"


SRCREV_FORMAT = "cargo_curl-rust_curl_ssh2-rs_git2-rs_rust-openssl"
EXTRA_OECARGO_PATHS = "\
	${WORKDIR}/curl-rust \
	${WORKDIR}/ssh2-rs \
	${WORKDIR}/git2-rs \
	${WORKDIR}/rust-openssl \
"

# FIXME: we don't actually use these, and shouldn't need to fetch it, but not having it results in:
## target/snapshot/bin/cargo build --target x86_64-linux  --verbose 
## Failed to resolve path '/home/cody/obj/y/tmp/work/x86_64-linux/cargo-native/git+gitAUTOINC+0b84923203_9181ea8f4e_8baa8ccb39-r0/curl-rust/curl-sys/curl/.git': No such file or directory
SRCREV_curl = "ac30e9a7746c8641f4871e59b831ec28530c5c73"
SRCREV_libgit2 = "3b48f7f30c271ec9569f722215ee55cc5e922242"
