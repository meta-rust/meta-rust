require rust.inc
require rust-source-${PV}.inc
require rust-snapshot-${PV}.inc

DEPENDS += "rust-llvm (=${PV})"

# Otherwise we'll depend on what we provide
INHIBIT_DEFAULT_RUST_DEPS_class-native = "1"
# We don't need to depend on gcc-native because yocto assumes it exists
PROVIDES_class-native = "virtual/${TARGET_PREFIX}rust"

# The default behaviour of x.py changed in 1.47+ so now we need to
# explicitly ask for the stage 2 compiler to be assembled.
do_compile () {
    rust_runx build --stage 2 src/rustc
}

BBCLASSEXTEND = "native"
