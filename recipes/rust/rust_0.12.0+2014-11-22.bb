SRCREV = "ccc4a7cebc759b3c8295b64bd5c1fe29fdb3db8a"
require rust-git.inc

SRC_URI_append = "\
	file://0001-platform.mk-avoid-choking-on-i586.patch \
	file://0002-mk-rt-compiler_rt-pass-LDFLAGS-from-CFG_GCCISH_LINK_.patch \
	file://0003-Target-add-default-target.json-path-libdir-rust-targ.patch \
	file://0004-mk-for-stage0-use-RUSTFLAGS-to-override-target-libs-.patch \
	file://0005-mk-add-missing-CFG_LIBDIR_RELATIVE.patch \
	file://0006-configure-support-bindir-and-extend-libdir-to-non-bl.patch \
	file://0007-XXX-remove-conflicting-realpath-hack.patch \
	file://0008-XXX-configure-unneeded-windows-check.patch \
"
