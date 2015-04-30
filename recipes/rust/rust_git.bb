# 2015-03-09
SRCREV = "9854143cba679834bc4ef932858cd5303f015a0e"
require rust-git.inc

SRC_URI_append = "\
	file://0003-platform.mk-avoid-choking-on-i586.patch \
	file://0004-Target-add-default-target.json-path-libdir-rust-targ.patch \
	file://0008-Parallelize-submake-invocations.patch \
	file://0009-std-thread_local-workaround-for-NULL-__dso_handle.patch \
	file://0010-configure-install-support-disabling-calling-of-ldcon.patch \
	file://0011-mk-install-use-disable-rewrite-paths.patch \
	file://0012-filesearch-add-info-to-show-path-searching.patch \
	file://0001-filesearch-support-RUST_SYSROOT-env-var.patch \
\
	file://rust-installer/0001-add-option-to-disable-rewriting-of-install-paths.patch;patchdir=src/rust-installer \
"
