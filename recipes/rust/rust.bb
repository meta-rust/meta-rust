require rust-release.inc
require rust.inc
require rust-version.inc

SRC_URI_append = "\
        file://rust/0001-platform.mk-avoid-choking-on-i586.patch \
        file://rust/0002-Target-add-default-target.json-path-libdir-rust-targ.patch \
        file://rust/0003-mk-for-stage0-use-RUSTFLAGS-to-override-target-libs-.patch \
        file://rust/0004-mk-add-missing-CFG_LIBDIR_RELATIVE.patch \
        file://rust/0005-configure-support-bindir-and-extend-libdir-to-non-bl.patch \
        file://rust/0006-std-thread_local-workaround-for-NULL-__dso_handle.patch \
        file://rust/0007-mk-install-use-disable-rewrite-paths.patch \
        file://rust/0008-install-disable-ldconfig.patch \
        file://rust/0009-Remove-crate-metadata-from-symbol-hashing.patch \
\
	file://rust-installer/0001-add-option-to-disable-rewriting-of-install-paths.patch;patchdir=src/rust-installer \
"
