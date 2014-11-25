inherit rust

CARGO = "cargo"

# Cargo only supports in-tree builds at the moment
B = "${S}"

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
		printf "\"%s\" " "$p"
	done | sed -e 's/[ \n]+/,/g'  -e 's/,$//' >>.cargo/config
	echo "]" >>.cargo/config
}

rust_cargo_patch () {
	cd "${S}"
	cat >>Cargo.toml <<EOF
[profile.dev]
rpath = true
[profile.release]
rpath = true
EOF
}

oe_cargo_build () {
	# FIXME: if there is already an entry for this target, in an existing
	# cargo/config, this won't work.
	which cargo
	which rustc
	bbnote ${CARGO} build --target ${TARGET_SYS} "$@"
	oe_cargo_config
	"${CARGO}" build -v --target "${TARGET_SYS}" --release "$@"
}

cargo_do_compile () {
	cd "${B}"
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
