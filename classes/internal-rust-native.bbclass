inherit native
PN = "rust-native"

# Otherwise we'll depend on what we provide
INHIBIT_DEFAULT_RUST_DEPS = "1"
# We don't need to depend on gcc-native because yocto assumes it exists
PROVIDES = "virtual/${TARGET_PREFIX}rust"

USE_LOCAL_NATIVE_RUST ??= "0"
USE_LOCAL_RUST ?= "${@base_conditional('USE_LOCAL_NATIVE_RUST', '0', '0', '1', d)}"
