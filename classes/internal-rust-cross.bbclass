inherit cross

# Otherwise we'll depend on what we provide
INHIBIT_DEFAULT_DEPS = "1"

DEPENDS += "virtual/${TARGET_PREFIX}gcc rust-native"
PROVIDES = "virtual/${TARGET_PREFIX}rust"
PN = "rust-cross-${TARGET_ARCH}"

# The same value as ${TOOLCHAIN_OPTIONS}. We can't use that variable directly
# here because cross.bblcass is "helpful" and blanks it out.
PRE_LINK_ARGS_PREPEND = "--sysroot=${STAGING_DIR_TARGET}"

## gcc-cross settings
# INHIBIT_DEFAULT_DEPS = "1"
# INHIBIT_PACKAGE_STRIP = "1"
# ARCH_FLAGS_FOR_TARGET += "-isystem${STAGING_DIR_NATIVE}${target_includedir}"

# cross.bbclass is "helpful" and overrides our do_install. Tell it not to.
do_install () {
	rust_do_install
}
