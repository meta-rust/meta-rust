inherit cross

# Otherwise we'll depend on what we provide
INHIBIT_DEFAULT_DEPS = "1"

DEPENDS += "virtual/${TARGET_PREFIX}gcc rust-native"
PROVIDES = "virtual/${TARGET_PREFIX}rust"
PN = "rust-cross-${TARGET_ARCH}"

## gcc-cross settings
# INHIBIT_DEFAULT_DEPS = "1"
# INHIBIT_PACKAGE_STRIP = "1"
# ARCH_FLAGS_FOR_TARGET += "-isystem${STAGING_DIR_NATIVE}${target_includedir}"

# TODO: use rust-native instead of a snapshot
EXTRA_OECONF += ""

# cross.bbclass is "helpful" and overrides our do_install. Tell it not to.
do_install () {
	rust_do_install
}
