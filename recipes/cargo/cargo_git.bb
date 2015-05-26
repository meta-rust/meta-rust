# 2015-03-23
SRCREV_cargo = "8d4bf72bf6b1f997c2e91ec57b79c6bbd2ed65e4"
SRCREV_rust-installer = "60fd8abfcae50629a3fc664bd809238fed039617"

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
\
\
	git://github.com/alexcrichton/curl.git;protocol=https;destsuffix=curl-rust/curl-sys/curl;name=curl;branch=configure \
	git://github.com/alexcrichton/libgit2.git;protocol=https;destsuffix=git2-rs/libgit2-sys/libgit2;name=libgit2;branch=libgit2-2014-12-19 \
"

# 0.2.3  / -sys 0.1.16
SRCREV_curl-rust = "8db3885f0e39c748c37d6f5409a055aa8412b81f"

# 0.2.3 / -sys 0.1.13
SRCREV_ssh2-rs = "20051a11312ff1769bd21c461232c0cb8bc99815"

# 0.2.5 / -sys 0.2.6
SRCREV_git2-rs = "7ba50b6e2170cc73ee55b8de738cf9efb68b6646"

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
SRCREV_libgit2 = "3b48f7f30c271ec9569f722215ee55cc5e922242"

CARGO_SNAPSHOT = "2015-04-02/cargo-nightly-x86_64-unknown-linux-gnu.tar.gz"
SRC_URI[md5sum] = "3d62194d02a9088cd8aae379e9498134"
SRC_URI[sha256sum] = "16b6338ba2942989693984ba4dbd057c2801e8805e6da8fa7b781b00e722d117"
