inherit cross

# Otherwise we'll depend on what we provide
INHIBIT_DEFAULT_RUST_DEPS = "1"
DEPENDS += "rust-native"
PROVIDES = "virtual/${TARGET_PREFIX}rust"
PN = "rust-cross-${TARGET_ARCH}"

# The same value as ${TOOLCHAIN_OPTIONS}. We can't use that variable directly
# here because cross.bblcass is "helpful" and blanks it out.
#TARGET_PRE_LINK_ARGS_append = " --sysroot=${STAGING_DIR_TARGET}"

# FIXME: the only way to convince cargo to include the rpath is via editing
# Config.toml, and doing that safely requires us to write actual patches
HOST_PRE_LINK_ARGS_append = " -Wl,-rpath=${libdir}"
BUILD_PRE_LINK_ARGS_append = " -Wl,-rpath=${libdir}"

# We need the same thing for the calls to the compiler when building the runtime crap
TARGET_CC_ARCH_append = " --sysroot=${STAGING_DIR_TARGET}"

## gcc-cross settings
# INHIBIT_DEFAULT_DEPS = "1"
# INHIBIT_PACKAGE_STRIP = "1"
# ARCH_FLAGS_FOR_TARGET += "-isystem${STAGING_DIR_NATIVE}${target_includedir}"

# cross.bbclass is "helpful" and overrides our do_install. Tell it not to.
do_install () {
	rust_do_install
}
