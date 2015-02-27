# 2015-02-21
SRCREV = "2b01a37ec38db9301239f0c0abcf3c695055b0ff"
require rust-git.inc

SRC_URI_append = "\
	file://0001-libstd-io-process-Command-fully-quote-and-escape-the.patch \
	file://0002-std-io-process-add-Debug-tests.patch \
	file://0003-platform.mk-avoid-choking-on-i586.patch \
	file://0004-mk-rt-compiler_rt-pass-LDFLAGS-from-CFG_GCCISH_LINK_.patch \
	file://0005-Target-add-default-target.json-path-libdir-rust-targ.patch \
	file://0006-mk-for-stage0-use-RUSTFLAGS-to-override-target-libs-.patch \
	file://0007-mk-add-missing-CFG_LIBDIR_RELATIVE.patch \
	file://0008-configure-support-bindir-and-extend-libdir-to-non-bl.patch \
	file://0009-Parallelize-submake-invocations.patch \
	file://0010-std-thread_local-workaround-for-NULL-__dso_handle.patch \
"
