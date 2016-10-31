# In order to share the same source between multiple packages (.bb files), we
# unpack and patch the rustc source here into a shared dir.
#
# Take a look at gcc-source.inc for the general structure of this

inherit shared-source-provide

require rust-version.inc
require rust-release.inc

SRC_URI[rust.md5sum] = "37ee9fc76712e4e94e14947c160bd6d0"
SRC_URI[rust.sha256sum] = "ac5907d6fa96c19bd5901d8d99383fb8755127571ead3d4070cce9c1fb5f337a"

LIC_FILES_CHKSUM = "file://COPYRIGHT;md5=eb87dba71cb424233bcce88db3ae2f1a"

SRC_URI_append = "\
	file://rust/0001-Target-add-default-target.json-path-libdir-rust-targ.patch \
	file://rust/0002-mk-for-stage0-use-RUSTFLAGS-to-override-target-libs-.patch \
	file://rust/0003-mk-add-missing-CFG_LIBDIR_RELATIVE.patch \
	file://rust/0004-configure-support-bindir-and-extend-libdir-to-non-bl.patch \
	file://rust/0005-std-thread_local-workaround-for-NULL-__dso_handle.patch \
	file://rust/0006-mk-install-use-disable-rewrite-paths.patch \
	file://rust/0007-Allow-overriding-crate_hash-with-C-crate_hash.patch \
	file://rust/0008-mk-platform.mk-pass-C-crate_hash-to-builds.patch \
	file://rust/0009-mk-allow-changing-the-platform-configuration-source-.patch \
	file://rust/0010-configure-llvm-pass-down-all-flags.patch \
        file://rust-installer/0001-add-option-to-disable-rewriting-of-install-paths.patch;patchdir=src/rust-installer \
"
