# 2015-06-29
SRCREV_cargo = "339a103fa71701541229316a568fca12cf07fc8d"
SRCREV_rust-installer = "8e4f8ea581502a2edc8177a040300e05ff7f91e3"

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
"

# 0.2.10  / -sys 0.1.24
SRCREV_curl-rust = "9fbf39fa8765e777d110ad18a2a2a3ea42dcb717"

# 0.2.8 / -sys 0.1.25
SRCREV_ssh2-rs = "afc39c6e7236b87d7ebde21ee4d4743d9437b85f"

# 0.2.11 / -sys 0.2.14
SRCREV_git2-rs = "3a7a990607a766fa65a40b920d70c8289691d2f8"

SRCREV_FORMAT .= "_curl-rust_curl_ssh2-rs_git2-rs"
EXTRA_OECARGO_PATHS = "\
	${WORKDIR}/curl-rust \
	${WORKDIR}/ssh2-rs \
	${WORKDIR}/git2-rs \
"

CARGO_SNAPSHOT = "2015-04-02/cargo-nightly-x86_64-unknown-linux-gnu.tar.gz"
SRC_URI[md5sum] = "3d62194d02a9088cd8aae379e9498134"
SRC_URI[sha256sum] = "16b6338ba2942989693984ba4dbd057c2801e8805e6da8fa7b781b00e722d117"

# Used in libgit2-sys's build.rs, needed for pkg-config to be used
export LIBSSH2_SYS_USE_PKG_CONFIG = "1"

# FIXME: we don't actually use these, and shouldn't need to fetch it, but not having it results in:
## target/snapshot/bin/cargo build --target x86_64-linux  --verbose 
## Failed to resolve path '/home/cody/obj/y/tmp/work/x86_64-linux/cargo-native/git+gitAUTOINC+0b84923203_9181ea8f4e_8baa8ccb39-r0/curl-rust/curl-sys/curl/.git': No such file or directory

SRC_URI += "\
	git://github.com/alexcrichton/curl.git;protocol=https;destsuffix=curl-rust/curl-sys/curl;name=curl;branch=configure \
	git://github.com/libgit2/libgit2.git;protocol=https;destsuffix=git2-rs/libgit2-sys/libgit2;name=libgit2 \
"
SRCREV_curl = "9a300aa13e5035a795396e429aa861229424c9dc"
SRCREV_libgit2 = "47f37400253210f483d84fb9c2ecf44fb5986849"
