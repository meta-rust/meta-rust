inherit rust-installer
require rust.inc
require rust-source-${PV}.inc

# the configure script always requires cmake so despite
# rust not needing this (only rust-llvm needs it) we must
# have it for the configure script to succeed.
DEPENDS += "cmake-native"

SRC_URI += " \
        file://rust-${PV}/0001-Target-add-default-target.json-path-libdir-rust-targ.patch \
        file://rust-${PV}/0002-mk-for-stage0-use-RUSTFLAGS-to-override-target-libs-.patch \
        file://rust-${PV}/0003-mk-add-missing-CFG_LIBDIR_RELATIVE.patch \
        file://rust-${PV}/0005-std-thread_local-workaround-for-NULL-__dso_handle.patch \
        file://rust-${PV}/0006-mk-install-use-disable-rewrite-paths.patch \
        file://rust-${PV}/0007-Allow-overriding-crate_hash-with-C-crate_hash.patch \
        file://rust-${PV}/0008-mk-platform.mk-pass-C-crate_hash-to-builds.patch \
        file://rust-installer-${PV}/0001-add-option-to-disable-rewriting-of-install-paths.patch;patchdir=src/rust-installer \
        "

DEPENDS += "rust-llvm (=${PV})"

# Otherwise we'll depend on what we provide
INHIBIT_DEFAULT_RUST_DEPS_class-native = "1"
# We don't need to depend on gcc-native because yocto assumes it exists
PROVIDES_class-native = "virtual/${TARGET_PREFIX}rust"

BBCLASSEXTEND = "native"
