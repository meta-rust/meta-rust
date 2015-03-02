# 2015-02-28
SRCREV = "e233987ce1de88a48db2ce612019ba644d3cf5dd"
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
	file://0011-configure-install-support-disabling-calling-of-ldcon.patch \
	file://0012-mk-install-use-disable-rewrite-paths.patch \
\
	file://rust-installer/0001-add-option-to-disable-rewriting-of-install-paths.patch;patchdir=src/rust-installer \
"
