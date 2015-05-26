# 2015-05-21
SRCREV_cargo = "3090cc3151389283ce5f733c66464c65f02aa659"
SRCREV_rust-installer = "e54d4823d26cdb3f98e5a1b17e1c257cd329aa61"

require cargo.inc

SRC_URI += " \
	git://github.com/carllerche/curl-rust.git;protocol=https;destsuffix=curl-rust;name=curl-rust \
	file://curl-rust/0001-curl-sys-avoid-explicitly-linking-in-openssl.-If-it-.patch;patchdir=../curl-rust \
	file://curl-rust/0002-remove-per-triple-deps-on-openssl-sys.patch;patchdir=../curl-rust \
\
	git://github.com/alexcrichton/ssh2-rs.git;protocol=https;name=ssh2-rs;destsuffix=ssh2-rs \
	file://ssh2-rs/0001-Unconditionally-depend-on-openssl-sys.patch;patchdir=../ssh2-rs \
\
	git://github.com/alexcrichton/git2-rs.git;protocol=https;name=git2-rs;destsuffix=git2-rs \
	file://git2-rs/0001-Add-generic-openssl-sys-dep.patch;patchdir=../git2-rs \
	file://git2-rs/0002-libgit2-sys-avoid-the-build-script-it-is-a-disaster.patch;patchdir=../git2-rs \
\
\
	git://github.com/alexcrichton/curl.git;protocol=https;destsuffix=curl-rust/curl-sys/curl;name=curl;branch=configure \
	git://github.com/libgit2/libgit2.git;protocol=https;destsuffix=git2-rs/libgit2-sys/libgit2;name=libgit2 \
"

# 0.2.10  / -sys 0.1.22
SRCREV_curl-rust = "00060b1be10cee2ef4ad4b6aa1f0bc34e85a3209"

# 0.2.7 / -sys 0.1.23
SRCREV_ssh2-rs = "340827c475174007f0d122795456f82ebd3431fb"

# 0.2.11 / -sys 0.2.14
SRCREV_git2-rs = "d8f056e802cebbffabe032c7f96e52e76262a11b"

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

CARGO_SNAPSHOT = "2015-04-02/cargo-nightly-x86_64-unknown-linux-gnu.tar.gz"
SRC_URI[md5sum] = "3d62194d02a9088cd8aae379e9498134"
SRC_URI[sha256sum] = "16b6338ba2942989693984ba4dbd057c2801e8805e6da8fa7b781b00e722d117"
