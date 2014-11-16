inherit native
PN = "rust-native"

USE_LOCAL_NATIVE_RUST ??= "0"
USE_LOCAL_RUST = "${base_conditional('USE_LOCAL_NATIVE_RUST', '0', '0', '1')}"
