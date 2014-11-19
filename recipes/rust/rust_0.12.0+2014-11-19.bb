SRCREV = "bfaa7bcab3459907014c31d3bf980f65ccd14b08"
require rust-git.inc

SRC_URI_append = "\
	file://0001-platform.mk-avoid-choking-on-i586.patch \
	file://0007-mk-rt-compiler_rt-pass-LDFLAGS-from-CFG_GCCISH_LINK_.patch \
	file://0030-Target-add-default-target.json-path-libdir-rust-targ.patch \
	file://0031-mk-cfg-add-.mk-suffix-on-files-to-avoid-supprises-wh.patch \
	file://0020-Support-bindir.patch \
	file://0021-Remember-relative-libdir-and-bindir-from-build-time.patch \
	file://0022-mk-add-missing-CFG_BINDIR_RELATIVE-uses.patch \
	file://0023-mk-add-missing-CFG_LIBDIR_RELATIVE.patch \
	file://0024-configure-CFG_-DIR_RELATIVE-avoid-requiring-existenc.patch \
	file://0025-mk-add-rule-to-create-bindir.patch \
	file://0026-mk-always-use-bin-as-bindir-for-stage0-CFG_BUILD-and.patch \
	file://0027-mk-stage0-complain-instead-of-creating-an-empty-file.patch \
	file://0028-mk-target-fix-typo-so-we-depend-on-the-correct-direc.patch \
	file://0029-rustdoc-avoid-supplying-a-bad-default-sysroot-so-the.patch \
"
