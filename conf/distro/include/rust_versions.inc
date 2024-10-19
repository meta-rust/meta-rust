# include this in your distribution to easily switch between versions
# just by changing RUST_VERSION variable

RUST_VERSION ?= "1.78.0"

PREFERRED_VERSION_cargo ?= "${RUST_VERSION}"
PREFERRED_VERSION_cargo-cross-canadian-${TARGET_ARCH} ?= "${RUST_VERSION}"
PREFERRED_VERSION_cargo-native ?= "${RUST_VERSION}"
PREFERRED_VERSION_nativesdk-cargo ?= "${RUST_VERSION}"
PREFERRED_VERSION_libstd-rs ?= "${RUST_VERSION}"
PREFERRED_VERSION_nativesdk-libstd-rs ?= "${RUST_VERSION}"
PREFERRED_VERSION_rust ?= "${RUST_VERSION}"
PREFERRED_VERSION_rust-cross-canadian-${TARGET_ARCH} ?= "${RUST_VERSION}"
PREFERRED_VERSION_rust-tools-cross-canadian-${TARGET_ARCH} ?= "${RUST_VERSION}"
PREFERRED_VERSION_rust-cross-${TARGET_ARCH} ?= "${RUST_VERSION}"
PREFERRED_VERSION_rust-cross-${DEFAULTTUNE}-${TCLIBC} ?= "${RUST_VERSION}"
PREFERRED_VERSION_rust-crosssdk-${SDK_ARCH}-${TCLIBC} ?= "${RUST_VERSION}"
PREFERRED_VERSION_rust-llvm ?= "${RUST_VERSION}"
PREFERRED_VERSION_rust-llvm-native ?= "${RUST_VERSION}"
PREFERRED_VERSION_rust-native ?= "${RUST_VERSION}"
