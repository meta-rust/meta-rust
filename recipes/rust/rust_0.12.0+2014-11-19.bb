SRCREV = "bfaa7bcab3459907014c31d3bf980f65ccd14b08"
require rust-git.inc

SRC_URI_append = "\
	file://0001-platform.mk-avoid-choking-on-i586.patch \
	file://0007-mk-rt-compiler_rt-pass-LDFLAGS-from-CFG_GCCISH_LINK_.patch \
	file://0030-Target-add-default-target.json-path-libdir-rust-targ.patch \
	file://0031-mk-cfg-add-.mk-suffix-on-files-to-avoid-supprises-wh.patch \
	file://0050-Support-bindir.patch \
	file://0051-Remember-relative-libdir-and-bindir-from-build-time.patch \
	file://0052-mk-add-missing-CFG_BINDIR_RELATIVE-uses.patch \
	file://0053-mk-add-missing-CFG_LIBDIR_RELATIVE.patch \
	file://0054-configure-CFG_-DIR_RELATIVE-avoid-requiring-existenc.patch \
	file://0055-mk-add-rule-to-create-bindir.patch \
	file://0056-mk-always-use-bin-as-bindir-for-stage0-CFG_BUILD-and.patch \
	file://0057-mk-stage0-complain-instead-of-creating-an-empty-file.patch \
	file://0058-mk-target-fix-typo-so-we-depend-on-the-correct-direc.patch \
	file://0059-rustdoc-avoid-supplying-a-bad-default-sysroot-so-the.patch \
	file://0060-src-etc-install.sh-use-LIBDIR-and-BINDIR-RELATIVE.patch \
	file://0061-configure-silence-warning-about-LOCAL_RUST_ROOT-bein.patch \
	file://0070-mk-rt-use-CFG_LLVM_TARGET-instead-of-plain-target-wh.patch \
"
