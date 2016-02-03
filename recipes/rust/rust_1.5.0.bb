require rust-release.inc
require rust.inc
require rust-${PV}.inc

# "patch-prefix"
PP = "rust-${PV}"
SRC_URI_append = "\
        file://${PP}/0001-platform.mk-avoid-choking-on-i586.patch \
        file://${PP}/0002-Target-add-default-target.json-path-libdir-rust-targ.patch \
        file://${PP}/0003-mk-for-stage0-use-RUSTFLAGS-to-override-target-libs-.patch \
        file://${PP}/0004-mk-add-missing-CFG_LIBDIR_RELATIVE.patch \
        file://${PP}/0005-configure-support-bindir-and-extend-libdir-to-non-bl.patch \
        file://${PP}/0006-std-thread_local-workaround-for-NULL-__dso_handle.patch \
        file://${PP}/0007-mk-install-use-disable-rewrite-paths.patch \
        file://${PP}/0008-install-disable-ldconfig.patch \
        file://${PP}/0009-Remove-crate-metadata-from-symbol-hashing.patch \
        file://${PP}/0010-rustc_trans-make-.note.rustc-look-more-like-debug-in.patch \
\
	file://rust-installer/0001-add-option-to-disable-rewriting-of-install-paths.patch;patchdir=src/rust-installer \
"
