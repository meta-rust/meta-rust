# 2015-05-26
SRCREV = "c654a07d29c77b5a023cb9d36dfc61811349f64e"
require rust-git.inc

RUST_SNAPSHOT = "rust-stage0-2015-04-27-857ef6e-linux-x86_64-94089740e48167c5975c92c139ae9c286764012f.tar.bz2"
SRC_URI[md5sum] = "e0d49475a787aaa9481ec0b1a28d1f7a"
SRC_URI[sha256sum] = "e7858a90c2c6c35299ebe2cb6425f3f84d0ba171dcbce20ff68295a1ff75c7e5"

SRC_URI_append = "\
	file://0001-platform.mk-avoid-choking-on-i586.patch \
	file://0002-Target-add-default-target.json-path-libdir-rust-targ.patch \
	file://0003-mk-for-stage0-use-RUSTFLAGS-to-override-target-libs-.patch \
	file://0004-mk-add-missing-CFG_LIBDIR_RELATIVE.patch \
	file://0005-configure-support-bindir-and-extend-libdir-to-non-bl.patch \
	file://0006-std-thread_local-workaround-for-NULL-__dso_handle.patch \
	file://0007-mk-install-use-disable-rewrite-paths.patch \
\
	file://rust-installer/0001-add-option-to-disable-rewriting-of-install-paths.patch;patchdir=src/rust-installer \
"
