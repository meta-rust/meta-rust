require rust.inc
require rust-source-${PV}.inc
require rust-snapshot-${PV}.inc

SRC_URI += "\
    file://0001-rustc_target-Fix-dash-vs-underscore-mismatches-in-op.patch \
    "

DEPENDS += "rust-llvm (=${PV})"

# Otherwise we'll depend on what we provide
INHIBIT_DEFAULT_RUST_DEPS_class-native = "1"
# We don't need to depend on gcc-native because yocto assumes it exists
PROVIDES_class-native = "virtual/${TARGET_PREFIX}rust"

do_compile () {
    rust_runx build --stage 2
}

rust_do_install() {
    rust_runx install
}

BBCLASSEXTEND = "native"
