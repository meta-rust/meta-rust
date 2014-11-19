SRCREV = "1e4e55aebc1a71b6674c00b8604efa6b1e2e52cd"
require rust-git.inc

SRC_URI_append = "\
	file://0001-platform.mk-avoid-choking-on-i586.patch \
	file://0001-src-etc-snapshot-support-triples-lacking-a-vendor.patch \
	file://0005-CFG_CFLAGS-is-only-used-for-jemalloc-rename-all-uses.patch \
	file://0006-mk-rt-jemalloc-pass-CFG_GCCISH_CFLAGS-inside-CC-inst.patch \
	file://0007-mk-rt-compiler_rt-pass-LDFLAGS-from-CFG_GCCISH_LINK_.patch \
	file://0020-Support-bindir.patch \
	file://0021-Remember-relative-libdir-and-bindir-from-build-time.patch \
	file://0022-mk-add-missing-CFG_BINDIR_RELATIVE-uses.patch \
	file://0023-mk-add-missing-CFG_LIBDIR_RELATIVE.patch \
	file://0024-mk-add-rule-to-create-bindir.patch \
	file://0025-mk-always-use-bin-and-lib-as-bindir-and-libdir-for-s.patch \
	file://0026-mk-stage0-complain-instead-of-creating-an-empty-file.patch \
	file://0027-mk-target-fix-typo-so-we-depend-on-the-correct-direc.patch \
	file://0028-rustdoc-avoid-supplying-a-bad-default-sysroot-so-the.patch \
	file://0030-Target-add-default-target.json-path-libdir-rust-targ.patch \
"
