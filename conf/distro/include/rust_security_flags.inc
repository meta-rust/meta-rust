# Build errors with PIE options enabled
SECURITY_CFLAGS_pn-rust-native = "${SECURITY_NO_PIE_CFLAGS}"
SECURITY_CFLAGS_pn-rust-cross-${TARGET_ARCH} = "${SECURITY_NO_PIE_CFLAGS}"
SECURITY_CFLAGS_pn-rust = "${SECURITY_NO_PIE_CFLAGS}"
SECURITY_CFLAGS_pn-rust-llvm = "${SECURITY_NO_PIE_CFLAGS}"

SECURITY_LDFLAGS_pn-rust-cross-arm = " -lssp_nonshared -lssp"
