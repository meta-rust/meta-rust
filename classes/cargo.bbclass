inherit rust-vars
# add crate fetch support
inherit crate-fetch
inherit rust-triples

# the binary we will use
CARGO = "cargo"

# Where we download our registry and dependencies to
export CARGO_HOME = "${WORKDIR}/cargo_home"

# We need cargo to compile for the target
BASEDEPENDS_append = " cargo-native"

# Ensure we get the right rust variant
DEPENDS_append_class-target = " virtual/${TARGET_PREFIX}rust ${RUSTLIB_DEP}"
DEPENDS_append_class-native = " rust-native"

# Cargo only supports in-tree builds at the moment
B = "${S}"

# In case something fails in the build process, give a bit more feedback on
# where the issue occured
export RUST_BACKTRACE = "1"

# The pkg-config-rs library used by cargo build scripts disables itself when
# cross compiling unless this is defined. We set up pkg-config appropriately
# for cross compilation, so tell it we know better than it.
export PKG_CONFIG_ALLOW_CROSS = "1"

cargo_do_configure () {
	mkdir -p ${CARGO_HOME}
	echo "paths = [" > ${CARGO_HOME}/config

	for p in ${EXTRA_OECARGO_PATHS}; do
		printf "\"%s\"\n" "$p"
	done | sed -e 's/$/,/' >> ${CARGO_HOME}/config
	echo "]" >> ${CARGO_HOME}/config

	# Point cargo at our local mirror of the registry
	cat >> ${CARGO_HOME}/config <<EOF
[source.local]
local-registry = "${WORKDIR}/cargo_registry"
[source.crates-io]
replace-with = "local"
registry = "https://github.com/rust-lang/crates.io-index"
EOF

	# We need to use the real Yocto linker and get the linker
	# flags to it. Yocto has the concept of BUILD and TARGET
	# and uses HOST to be the currently selected one. However
	# LDFLAGS and TOOLCHAIN_OPTIONS are not prefixed with HOST
	echo "[build]" >> ${CARGO_HOME}/config
	echo "rustflags = [" >> ${CARGO_HOME}/config
	echo "'-C'," >> ${CARGO_HOME}/config
	echo "'link-args=${LDFLAGS}${HOST_CC_ARCH}${TOOLCHAIN_OPTIONS}'," >> ${CARGO_HOME}/config
	for p in ${RUSTFLAGS}; do
		printf "'%s'\n" "$p"
	done | sed -e 's/$/,/' >> ${CARGO_HOME}/config
	echo "]" >> ${CARGO_HOME}/config
	echo "[target.${RUST_HOST_SYS}]" >> ${CARGO_HOME}/config
	echo "linker = '${RUST_TARGET_CCLD}'" >> ${CARGO_HOME}/config
}

# All the rust & cargo ecosystem assume that CC, LD, etc are a path to a single
# command. Fixup the ones we give it so that is the case.
# XXX: this is hard coded based on meta/conf/bitbake.conf
# TODO: we do quite a bit very similar to this in rust.inc, see if it can be
# generalized.
export RUST_CFLAGS = "${HOST_CC_ARCH}${TOOLCHAIN_OPTIONS} ${CFLAGS}"
export RUST_BUILD_CFLAGS = "${BUILD_CC_ARCH} ${BUILD_CFLAGS}"

CARGO_BUILD_FLAGS = "-v --target ${HOST_SYS} --release"

# This is based on the content of CARGO_BUILD_FLAGS and generally will need to
# change if CARGO_BUILD_FLAGS changes.
CARGO_TARGET_SUBDIR="${HOST_SYS}/release"
oe_cargo_build () {
	unset RUSTFLAGS
	bbnote "cargo = $(which cargo)"
	bbnote "rustc = $(which rustc)"
	bbnote "${CARGO} build ${CARGO_BUILD_FLAGS} $@"
	"${CARGO}" build ${CARGO_BUILD_FLAGS} "$@"
}

oe_cargo_fix_env () {
	export CC="${RUST_TARGET_CC}"
	export CFLAGS="${RUST_CFLAGS}"
	export AR="${AR}"
	export TARGET_CC="${RUST_TARGET_CC}"
	export TARGET_CFLAGS="${RUST_CFLAGS}"
	export TARGET_AR="${AR}"
	export HOST_CC="${RUST_BUILD_CC}"
	export HOST_CFLAGS="${RUST_BUILD_CFLAGS}"
	export HOST_AR="${BUILD_AR}"
}

EXTRA_OECARGO_PATHS ??= ""

cargo_do_compile () {
	# prevent cargo from trying to fetch down new data
	mkdir -p "${WORKDIR}/cargo_home/registry/index/github.com-1ecc6299db9ec823"
	touch "${WORKDIR}/cargo_home/registry/index/github.com-1ecc6299db9ec823/.cargo-index-lock"

	oe_cargo_fix_env
	oe_cargo_build
}

cargo_do_install () {
	local have_installed=false
	for tgt in "${B}/target/${CARGO_TARGET_SUBDIR}/"*; do
		if [[ $tgt == *.so || $tgt == *.rlib ]]; then
			install -d "${D}${rustlibdir}"
			install -m755 "$tgt" "${D}${rustlibdir}"
			have_installed=true
		elif [ -f "$tgt" ] && [ -x "$tgt" ]; then
			install -d "${D}${bindir}"
			install -m755 "$tgt" "${D}${bindir}"
			have_installed=true
		fi
	done
	if ! $have_installed; then
		die "Did not find anything to install"
	fi
}

EXPORT_FUNCTIONS do_configure do_compile do_install
