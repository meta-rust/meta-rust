SRCREV = "1e4e55aebc1a71b6674c00b8604efa6b1e2e52cd"
require rust-git.inc

SRC_URI_append = "\
	file://0001-src-etc-snapshot-support-triples-lacking-a-vendor.patch \
	file://0001-get-snapshot-debug.patch \
	file://0001-platform.mk-avoid-choking-on-i586.patch \
	file://0005-CFG_CFLAGS-is-only-used-for-jemalloc-rename-all-uses.patch \
	file://0006-mk-rt-jemalloc-pass-CFG_GCCISH_CFLAGS-inside-CC-inst.patch \
	file://0007-mk-rt-compiler_rt-pass-LDFLAGS-from-CFG_GCCISH_LINK_.patch \
	file://0008-Support-bindir.patch \
	file://0009-Remember-relative-libdir-and-bindir-from-build-time.patch \
	file://0010-Target-add-default-target.json-path-libdir-rust-targ.patch \
	file://0011-rustc_back-target-add-debug-output-for-target-search.patch \
	file://0012-mk-add-missing-CFG_BINDIR_RELATIVE-uses.patch \
	file://0013-mk-add-missing-CFG_LIBDIR_RELATIVE.patch \
	file://0014-configure-CFG_-DIR_RELATIVE-avoid-requiring-existenc.patch \
	file://0015-mk-add-rule-to-create-bindir-unconditionalize-rule-t.patch \
"
