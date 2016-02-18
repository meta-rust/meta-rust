inherit rust

CARGO ?= "cargo"
export CARGO_HOME = "${WORKDIR}/cargo_home"

def cargo_base_dep(d):
    deps = ""
    if not d.getVar('INHIBIT_DEFAULT_DEPS', True) and not d.getVar('INHIBIT_CARGO_DEP', True):
        deps += " cargo-native"
    return deps

BASEDEPENDS_append = " ${@cargo_base_dep(d)}"

# FIXME: this is a workaround for a misbehavior in cargo when used with quilt.
# See https://github.com/rust-lang/cargo/issues/978
PATCHTOOL = "patch"

# Cargo only supports in-tree builds at the moment
B = "${S}"


# In case something fails in the build process, give a bit more feedback on
# where the issue occured
export RUST_BACKTRACE = "1"

# The pkg-config-rs library used by cargo build scripts disables itself when
# cross compiling unless this is defined. We set up pkg-config appropriately
# for cross compilation, so tell it we know better than it.
export PKG_CONFIG_ALLOW_CROSS = "1"

EXTRA_OECARGO_PATHS ??= ""

cargo_do_configure () {
	# FIXME: we currently make a mess in the directory above us
	# (${WORKDIR}), which may not be ideal. Look into whether this is
	# allowed
	mkdir -p ../.cargo
	# NOTE: we cannot pass more flags via this interface, the 'linker' is
	# assumed to be a path to a binary. If flags are needed, a wrapper must
	# be used.
	echo "paths = [" >../.cargo/config

	for p in ${EXTRA_OECARGO_PATHS}; do
		printf "\"%s\"\n" "$p"
	done | sed -e 's/$/,/' >>../.cargo/config
	echo "]" >>../.cargo/config
}

rust_cargo_patch () {
	# FIXME: if there is already an entry for this target, in an existing
	# cargo/config, this won't work.
	cd "${S}"
	cat >>Cargo.toml <<EOF
[profile.dev]
rpath = true
[profile.release]
rpath = true
EOF
}

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
	which cargo
	which rustc
	bbnote ${CARGO} build ${CARGO_BUILD_FLAGS} "$@"
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

cargo_do_compile () {
	cd "${B}"
	oe_cargo_fix_env
	oe_cargo_build
}

# All but the most simple projects will need to override this.
cargo_do_install () {
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

EXPORT_FUNCTIONS do_compile do_install do_configure
