# 2015-03-09
SRCREV_cargo = "e3a642559d25e4f3df494894bd03400924ee33ea"
SRCREV_rust-installer = "e54d4823d26cdb3f98e5a1b17e1c257cd329aa61"

require cargo.inc

SRC_URI += " \
	git://github.com/carllerche/curl-rust.git;protocol=https;destsuffix=curl-rust;name=curl-rust \
	file://curl-rust/0001-curl-sys-avoid-explicitly-linking-in-openssl.-If-it-.patch;patchdir=../curl-rust \
\
	git://github.com/alexcrichton/ssh2-rs.git;protocol=https;name=ssh2-rs;destsuffix=ssh2-rs \
	file://ssh2-rs/0001-Unconditionally-depend-on-openssl-sys.patch;patchdir=../ssh2-rs \
	file://curl-rust/0002-remove-per-triple-deps-on-openssl-sys.patch;patchdir=../curl-rust \
\
	git://github.com/alexcrichton/git2-rs.git;protocol=https;name=git2-rs;destsuffix=git2-rs \
	file://git2-rs/0001-Add-generic-openssl-sys-dep.patch;patchdir=../git2-rs \
	file://git2-rs/0001-i-don-t-understand-why-this-didn-t-build.patch;patchdir=../git2-rs \
\
	git://github.com/alexcrichton/curl.git;protocol=https;destsuffix=curl-rust/curl-sys/curl;name=curl;branch=configure \
	git://github.com/libgit2/libgit2.git;protocol=https;destsuffix=git2-rs/libgit2-sys/libgit2;name=libgit2 \
"

# 0.2.8  / -sys 0.1.21
SRCREV_curl-rust = "4655bcbf34ea6af28c43a586caf82a141bf48cff"

# 0.2.7 / -sys 0.1.18
SRCREV_ssh2-rs = "cce73bddc574715c0eb77ec5450a76840d43df81"

# 0.2.8 / -sys 0.2.11
SRCREV_git2-rs = "f70411bc2abe3ed0750ea0e8363814ad315a8542"

SRCREV_FORMAT .= "_curl-rust_curl_ssh2-rs_git2-rs"
EXTRA_OECARGO_PATHS = "\
	${WORKDIR}/curl-rust \
	${WORKDIR}/ssh2-rs \
	${WORKDIR}/git2-rs \
"

# FIXME: we don't actually use these, and shouldn't need to fetch it, but not having it results in:
## target/snapshot/bin/cargo build --target x86_64-linux  --verbose 
## Failed to resolve path '/home/cody/obj/y/tmp/work/x86_64-linux/cargo-native/git+gitAUTOINC+0b84923203_9181ea8f4e_8baa8ccb39-r0/curl-rust/curl-sys/curl/.git': No such file or directory
SRCREV_curl = "ac30e9a7746c8641f4871e59b831ec28530c5c73"
SRCREV_libgit2 = "47f37400253210f483d84fb9c2ecf44fb5986849"
