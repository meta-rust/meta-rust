
RUSTC = "rustc"
RUSTC_ARCHFLAGS += "--target=target"


# BUILD_LDFLAGS
# 	${STAGING_LIBDIR_NATIVE}
# 	${STAGING_BASE_LIBDIR_NATIVE}
# BUILDSDK_LDFLAGS
# 	${STAGING_LIBDIR}
# 	#{STAGING_DIR_HOST}
# TARGET_LDFLAGS ?????
#RUSTC_BUILD_LDFLAGS = "\
#	--sysroot ${STAGING_DIR_NATIVE} \
#	-L${STAGING_LIBDIR_NATIVE}	\
#	-L${STAGING_BASE_LIBDIR_NATIVE}	\
#"

RUST_PATH_NATIVE="${STAGING_LIBDIR_NATIVE}:${STAGING_BASE_LIBDIR_NATIVE}"

# FIXME: set based on whether we are native vs cross vs buildsdk, etc
RUST_PATH = "${RUST_PATH_NATIVE}"

CARGO = "cargo"

OECARGO_PATH ??= ""

oe_runrustc () {
	bbnote ${RUSTC} ${RUSTC_ARCHFLAGS} ${RUSTC_FLAGS} "$@"
	"${RUSTC}" ${RUSTC_ARCHFLAGS} ${RUSTC_FLAGS} "$@"
}

oe_cargo_config () {
	mkdir -p .cargo
	# FIXME: we currently blow away the entire config because duplicate
	# sections are treated as a parse error by cargo (causing the entire
	# config to be silently ignored.
	# NOTE: we cannot pass more flags via this interface, the 'linker' is
	# assumed to be a path to a binary. If flags are needed, a wrapper must
	# be used.
	cat >.cargo/config <<EOF
paths = [
EOF
	for p in ${OECARGO_PATH}; do
		printf "\"%s\" " "$p" 
	done | sed -e 's/[ \n]+/,/g'  -e 's/,$//' >>.cargo/config
	cat >>.cargo/config <<EOF
]

[target.${RUST_TARGET_SYS}]
ar = "${TARGET_PREFIX}ar"
linker = "${TARGET_PREFIX}gcc"
EOF
}

oe_cargo_patch () {
	cat >>Cargo.toml <<EOF
[profile.dev]
rpath = true
EOF
}

oe_runcargo_build () {
	# FIXME: if there is already an entry for this target, in an existing
	# cargo/config, this won't work.
	which cargo
	bbnote ${CARGO} build --target ${RUST_TARGET_SYS} "$@"
	oe_cargo_config
	export RUST_PATH="${RUST_PATH}"
	"${CARGO}" build -v --target "${RUST_TARGET_SYS}" --release "$@"
}
