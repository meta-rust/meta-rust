# 2015-06-26
SRCREV = "378a370ff2057afeb1eae86eb6e78c476866a4a6"
require rust-git.inc

RS_DATE = "2015-05-24"
RS_SRCHASH = "ba0e1cd"
# linux-x86_64
RS_HASH = "5fd8698fdfe953e6c4d86cf4fa1d5f3a0053248c"
RUST_SNAPSHOT = "rust-stage0-${RS_DATE}-${RS_SRCHASH}-linux-x86_64-${RS_HASH}.tar.bz2"

SRC_URI[rust-snapshot.md5sum] = "e0d49475a787aaa9481ec0b1a28d1f7a"
SRC_URI[rust-snapshot.sha256sum] = "e7858a90c2c6c35299ebe2cb6425f3f84d0ba171dcbce20ff68295a1ff75c7e5"

# "patch-prefix"
PP = "rust-git"
SRC_URI_append = "\
	file://${PP}/0001-platform.mk-avoid-choking-on-i586.patch \
	file://${PP}/0002-Target-add-default-target.json-path-libdir-rust-targ.patch \
	file://${PP}/0003-mk-for-stage0-use-RUSTFLAGS-to-override-target-libs-.patch \
	file://${PP}/0004-mk-add-missing-CFG_LIBDIR_RELATIVE.patch \
	file://${PP}/0005-configure-support-bindir-and-extend-libdir-to-non-bl.patch \
	file://${PP}/0006-std-thread_local-workaround-for-NULL-__dso_handle.patch \
	file://${PP}/0007-mk-install-use-disable-rewrite-paths.patch \
	file://${PP}/0008-install-disable-ldconfig.patch \
\
	file://rust-installer/0001-add-option-to-disable-rewriting-of-install-paths.patch;patchdir=src/rust-installer \
"

DEFAULT_PREFERENCE = "-1"
