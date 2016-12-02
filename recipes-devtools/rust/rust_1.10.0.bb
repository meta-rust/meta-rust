inherit rust-installer
require rust.inc
require rust-source-${PV}.inc

# overriden due to difference between 1.10.0 and 1.12.1
DATA_LAYOUT[aarch64] = "e-m:e-i64:64-i128:128-n32:64-S128"

SRC_URI += " \
        file://rust-${PV}/0001-Add-config-for-musl-based-arm-builds.patch \
        file://rust-${PV}/0002-Target-add-default-target.json-path-libdir-rust-targ.patch \
        file://rust-${PV}/0003-mk-for-stage0-use-RUSTFLAGS-to-override-target-libs-.patch \
        file://rust-${PV}/0004-mk-add-missing-CFG_LIBDIR_RELATIVE.patch \
        file://rust-${PV}/0006-std-thread_local-workaround-for-NULL-__dso_handle.patch \
        file://rust-${PV}/0007-mk-install-use-disable-rewrite-paths.patch \
        file://rust-${PV}/0008-Allow-overriding-crate_hash-with-C-crate_hash.patch \
        file://rust-${PV}/0009-mk-platform.mk-pass-C-crate_hash-to-builds.patch \
        file://rust-${PV}/0011-Get-rid-of-the-.note-interpretation-of-rustc-dylib-m.patch \
        file://rust-installer-${PV}/0001-add-option-to-disable-rewriting-of-install-paths.patch;patchdir=src/rust-installer \
        "

DEPENDS += "rust-llvm (=${PV})"

# Otherwise we'll depend on what we provide
INHIBIT_DEFAULT_RUST_DEPS_class-native = "1"
# We don't need to depend on gcc-native because yocto assumes it exists
PROVIDES_class-native = "virtual/${TARGET_PREFIX}rust"

BBCLASSEXTEND = "native"
