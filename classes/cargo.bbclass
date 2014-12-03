inherit rust

CARGO = "cargo"

def cargo_base_dep(d):
    deps = ""
    if not d.getVar('INHIBIT_DEFAULT_DEPS') and not d.getVar('INHIBIT_CARGO_DEP'):
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

EXTRA_OECARGO_PATHS ??= ""

oe_cargo_config () {
	mkdir -p .cargo
	# FIXME: we currently blow away the entire config because duplicate
	# sections are treated as a parse error by cargo (causing the entire
	# config to be silently ignored.
	# NOTE: we cannot pass more flags via this interface, the 'linker' is
	# assumed to be a path to a binary. If flags are needed, a wrapper must
	# be used.
	echo "paths = [" >.cargo/config

	for p in ${EXTRA_OECARGO_PATHS}; do
		printf "\"%s\"\n" "$p"
	done | sed -e 's/$/,/' >>.cargo/config
	echo "]" >>.cargo/config
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

oe_cargo_build () {
	which cargo
	which rustc
	bbnote ${CARGO} build --target ${TARGET_SYS} "$@"
	oe_cargo_config
	"${CARGO}" build -v --target "${TARGET_SYS}" --release "$@"
}

cargo_do_compile () {
	cd "${B}"
	export CC="${RUST_CC}"
	export CFLAGS="${RUST_CFLAGS}"
	export HOST_CC="${RUST_BUILD_CC}"
	export HOST_CFLAGS="${RUST_BUILD_CFLAGS}"
	oe_cargo_build
}

cargo_do_install () {
	install -d "${D}${bindir}"
	for tgt in "${B}/target/${HOST_SYS}/release/"*; do
		if [ -f "$tgt" ] && [ -x "$tgt" ]; then
			install -m755 "$tgt" "${D}${bindir}"
		fi
	done
}

EXPORT_FUNCTIONS do_compile do_install
