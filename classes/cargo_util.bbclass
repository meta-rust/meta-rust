# add crate fetch support
inherit crate-fetch

# the binary we will use
CARGO = "cargo"

# Where we download our registry and dependencies to
export CARGO_HOME = "${WORKDIR}/cargo_home"

# We need cargo to compile for the target
BASEDEPENDS_append = " cargo-native"

# Ensure we get the right rust variant
DEPENDS_append_class-target = "virtual/${TARGET_PREFIX}rust"

# Cargo only supports in-tree builds at the moment
B = "${S}"

# In case something fails in the build process, give a bit more feedback on
# where the issue occured
export RUST_BACKTRACE = "1"

# The pkg-config-rs library used by cargo build scripts disables itself when
# cross compiling unless this is defined. We set up pkg-config appropriately
# for cross compilation, so tell it we know better than it.
export PKG_CONFIG_ALLOW_CROSS = "1"

# All the rust & cargo ecosystem assume that CC, LD, etc are a path to a single
# command. Fixup the ones we give it so that is the case.
# XXX: this is hard coded based on meta/conf/bitbake.conf
# TODO: we do quite a bit very similar to this in rust.inc, see if it can be
# generalized.
export RUST_CC = "${CCACHE}${HOST_PREFIX}gcc"
export RUST_CFLAGS = "${HOST_CC_ARCH}${TOOLCHAIN_OPTIONS} ${CFLAGS}"
export RUST_BUILD_CC = "${CCACHE}${BUILD_PREFIX}gcc"
export RUST_BUILD_CFLAGS = "${BUILD_CC_ARCH} ${BUILD_CFLAGS}"

export CARGO_BUILD_FLAGS = "-v --target ${HOST_SYS} --release"

# This is based on the content of CARGO_BUILD_FLAGS and generally will need to
# change if CARGO_BUILD_FLAGS changes.
export CARGO_TARGET_SUBDIR="${HOST_SYS}/release"
oe_cargo_build () {
	bbnote "cargo = $(which cargo)"
	bbnote "rustc = $(which rustc)"
	bbnote "${CARGO} build ${CARGO_BUILD_FLAGS} $@"
	"${CARGO}" build ${CARGO_BUILD_FLAGS} "$@"
}

oe_cargo_fix_env () {
	export CC="${RUST_CC}"
	export CFLAGS="${RUST_CFLAGS}"
	export AR="${AR}"
	export TARGET_CC="${RUST_CC}"
	export TARGET_CFLAGS="${RUST_CFLAGS}"
	export TARGET_AR="${AR}"
	export HOST_CC="${RUST_BUILD_CC}"
	export HOST_CFLAGS="${RUST_BUILD_CFLAGS}"
	export HOST_AR="${BUILD_AR}"
}

cargo_util_do_compile () {
	cd "${B}"

	# prevent cargo from trying to fetch down new data
	mkdir -p "${WORKDIR}/cargo_home/registry/index/"
	touch "${WORKDIR}/cargo_home/registry/index/.cargo-index-lock"

	oe_cargo_fix_env
	oe_cargo_build
}

# All but the most simple projects will need to override this.
cargo_util_do_install () {
	local have_installed=false
	install -d "${D}${bindir}"
	for tgt in "${B}/target/${CARGO_TARGET_SUBDIR}/"*; do
		if [ -f "$tgt" ] && [ -x "$tgt" ]; then
			install -m755 "$tgt" "${D}${bindir}"
			have_installed=true
		fi
	done
	if ! $have_installed; then
		die "Did not find anything to install"
	fi
}

EXPORT_FUNCTIONS do_compile do_install
