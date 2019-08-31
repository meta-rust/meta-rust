##
## Purpose:
## This class is to support building with cargo. It
## must be different than cargo.bbclass because Rust
## now builds with Cargo but cannot use cargo.bbclass
## due to dependencies and assumptions in cargo.bbclass
## that Rust & Cargo are already installed. So this
## is used by cargo.bbclass and Rust
##

# add crate fetch support
inherit crate-fetch
inherit rust-common

# Where we download our registry and dependencies to
export CARGO_HOME = "${WORKDIR}/cargo_home"

# The pkg-config-rs library used by cargo build scripts disables itself when
# cross compiling unless this is defined. We set up pkg-config appropriately
# for cross compilation, so tell it we know better than it.
export PKG_CONFIG_ALLOW_CROSS = "1"

# Don't instruct cargo to use crates downloaded by bitbake. Some rust packages,
# for example the rust compiler itself, come with their own vendored sources.
# Specifying two [source.crates-io] will not work.
CARGO_DISABLE_BITBAKE_VENDORING ?= "0"

# Used by libstd-rs to point to the vendor dir included in rustc src
CARGO_VENDORING_DIRECTORY ?= "${CARGO_HOME}/bitbake"

cargo_common_do_configure () {
	mkdir -p ${CARGO_HOME}/bitbake
	echo "paths = [" > ${CARGO_HOME}/config

	for p in ${EXTRA_OECARGO_PATHS}; do
		printf "\"%s\"\n" "$p"
	done | sed -e 's/$/,/' >> ${CARGO_HOME}/config
	echo "]" >> ${CARGO_HOME}/config

	# Point cargo at our local mirror of the registry
	cat <<- EOF >> ${CARGO_HOME}/config
	[source.bitbake]
	directory = "${CARGO_VENDORING_DIRECTORY}"
	EOF

	if [ -z "${EXTERNALSRC}" ] && [ ${CARGO_DISABLE_BITBAKE_VENDORING} = "0" ]; then
		cat <<- EOF >> ${CARGO_HOME}/config
		[source.crates-io]
		replace-with = "bitbake"
		local-registry = "/nonexistant"
		EOF
	fi

        # Disable multiplexing in order to keep cargo from using http2, which we
        # can't currently enable because of dependency loops
        cat <<- EOF >> ${CARGO_HOME}/config
		[http]
		multiplexing = false
	EOF

	# When a sstate-cache is used sometimes the certificates are not available
	# at the compile time path anymore. Set it explicitly instead.
	echo "cainfo = \"${STAGING_ETCDIR_NATIVE}/ssl/certs/ca-certificates.crt\"" \
		>> ${CARGO_HOME}/config

	if [ -n "${http_proxy}" ]; then
		echo "proxy = \"${http_proxy}\"" >> ${CARGO_HOME}/config
	fi

	echo "[target.${HOST_SYS}]" >> ${CARGO_HOME}/config
	echo "linker = '${RUST_TARGET_CCLD}'" >> ${CARGO_HOME}/config
	if [ "${HOST_SYS}" != "${BUILD_SYS}" ]; then
		echo "[target.${BUILD_SYS}]" >> ${CARGO_HOME}/config
		echo "linker = '${RUST_BUILD_CCLD}'" >> ${CARGO_HOME}/config
	fi
}

oe_cargo_fix_env () {
	export CC="${RUST_TARGET_CC}"
	export CXX="${RUST_TARGET_CXX}"
	export CFLAGS="${CFLAGS}"
	export CXXFLAGS="${CXXFLAGS}"
	export AR="${AR}"
	export TARGET_CC="${RUST_TARGET_CC}"
	export TARGET_CXX="${RUST_TARGET_CXX}"
	export TARGET_CFLAGS="${CFLAGS}"
	export TARGET_CXXFLAGS="${CXXFLAGS}"
	export TARGET_AR="${AR}"
	export HOST_CC="${RUST_BUILD_CC}"
	export HOST_CXX="${RUST_BUILD_CXX}"
	export HOST_CFLAGS="${BUILD_CFLAGS}"
	export HOST_CXXFLAGS="${BUILD_CXXFLAGS}"
	export HOST_AR="${BUILD_AR}"
}

EXTRA_OECARGO_PATHS ??= ""

EXPORT_FUNCTIONS do_configure
