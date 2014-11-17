inherit cross

# Otherwise we'll depend on what we provide
INHIBIT_DEFAULT_DEPS = "1"

# XXX: will this glibc be correctly parsed? (glibc doesn't provice a virtual/${TARGET_PREFIX}libc)
DEPENDS += "virtual/${TARGET_PREFIX}gcc rust-native glibc"
PROVIDES = "virtual/${TARGET_PREFIX}rust"
PN = "rust-cross-${TARGET_ARCH}"

# The same value as ${TOOLCHAIN_OPTIONS}. We can't use that variable directly
# here because cross.bblcass is "helpful" and blanks it out.
TARGET_PRE_LINK_ARGS_PREPEND_append = " --sysroot=${STAGING_DIR_TARGET}"

# We need the same thing for the calls to the compiler when building the runtime crap
TARGET_CC_ARCH_append += " --sysroot=${STAGING_DIR_TARGET}"

## gcc-cross settings
# INHIBIT_DEFAULT_DEPS = "1"
# INHIBIT_PACKAGE_STRIP = "1"
# ARCH_FLAGS_FOR_TARGET += "-isystem${STAGING_DIR_NATIVE}${target_includedir}"

# cross.bbclass is "helpful" and overrides our do_install. Tell it not to.
do_install () {
	rust_do_install
}
