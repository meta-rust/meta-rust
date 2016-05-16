inherit rust

CARGO ?= "cargo"
export CARGO_HOME = "${WORKDIR}/cargo_home"

# Maintain a cargo index in the sysroot publishing locally built crates
LOCAL_CARGO_INDEX ?= "1"
CREATE_LOCAL_CARGO_INDEX ?= "${LOCAL_CARGO_INDEX}"

def cargo_base_dep(d):
    deps = ""
    if not d.getVar('INHIBIT_DEFAULT_DEPS', True) and not d.getVar('INHIBIT_CARGO_DEP', True):
        deps += " cargo-native"
    return deps

BASEDEPENDS_append = " ${@cargo_base_dep(d)}"

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

	if [ "${LOCAL_CARGO_INDEX}" == "1" ]; then
		echo '[registry]' >>../.cargo/config
		echo 'index="file://${LOCAL_CARGO_INDEX_DIR}"' >>../.cargo/config
	fi
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

# Tell cargo to build out-of-tree
B = "${WORKDIR}/build"
export CARGO_TARGET_DIR = "${B}"
# This is based on the content of CARGO_BUILD_FLAGS and generally will need to
# change if CARGO_BUILD_FLAGS changes.
export CARGO_TARGET_SUBDIR="${HOST_SYS}/release"
oe_cargo_build () {
	cd "${S}"
	rm -rf ${B}
	export RUSTFLAGS="${RUSTFLAGS}"
	which cargo
	which rustc
	bbnote ${CARGO} build ${CARGO_BUILD_FLAGS} "$@"
	"${CARGO}" build ${CARGO_BUILD_FLAGS} "$@"
	"${CARGO}" package --no-verify
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

CARGO_INDEX_DIR = "${datadir}/cargo/index"
CARGO_INDEX_DEST = "${D}/${CARGO_INDEX_DIR}"
CARGO_CRATE_DIR = "${datadir}/cargo/crates"
CARGO_CRATE_DEST = "${D}/${CARGO_CRATE_DIR}"
LOCAL_CARGO_INDEX_DIR = "${WORKDIR}/cargo_index"

do_cargo_create_registry () {
    cp -al ${STAGING_DIR_HOST}/${CARGO_INDEX_DIR}/* ${LOCAL_CARGO_INDEX_DIR} || true
    echo '{
    "dl": "file://${STAGING_DIR_HOST}/${CARGO_CRATE_DIR}",
    "api": "invalid"
}' >config.json
    git init
    git add .
    git commit -m "registry"
}
do_cargo_create_registry[dirs] = "${LOCAL_CARGO_INDEX_DIR}"
do_cargo_create_registry[cleandirs] = "${LOCAL_CARGO_INDEX_DIR} ${CARGO_HOME}"
do_configure[prefuncs] += "${@base_conditional('CREATE_LOCAL_CARGO_INDEX', '1', 'do_cargo_create_registry', '', d)}"

python do_cargo_publish_registry () {
    import os
    import json
    import hashlib
    import shutil
    import subprocess

    os.chdir(d.getVar("S", True))
    cargo = d.getVar("CARGO", True)
    output = subprocess.check_output(cargo + " read-manifest", shell=True)
    pkg = json.loads(output)

    # Massage json into registry format
    pkg["vers"] = pkg["version"]
    pkg["deps"] = pkg["dependencies"]
    pkg["yanked"] = False

    cratefile = os.path.join(d.getVar("CARGO_TARGET_DIR", True), "package",
                             pkg["name"] + "-" + pkg["vers"] + ".crate")
    with open(cratefile, 'rb') as f:
        pkg["cksum"] = hashlib.sha256(f.read()).hexdigest()

    wanted_keys = ("name", "vers" ,"deps", "cksum", "features", "yanked")
    # Filter out unwanted metadata
    pkg = { k: pkg[k] for k in pkg if k in wanted_keys }

    missing = set(wanted_keys) - set(pkg)
    if missing:
        raise bb.build.FuncFailed("Missing keys %s in pkg manifest" % missing)

    name = pkg["name"]
    if len(name) == 1:
        path = os.path.join("1")
    elif len(name) == 2:
        path = os.path.join("2")
    elif len(name) == 3:
        path = os.path.join("3", name[0])
    else:
        path = os.path.join(name[:2], name[2:4])
    index = d.getVar("CARGO_INDEX_DEST", True)
    path = os.path.join(index, path)
    bb.utils.mkdirhier(path)
    path = os.path.join(path, name)
    with open(path, "w") as f:
        f.write(json.dumps(pkg))

    # Move the crate into the download dir
    # Yes, the file name is "download"
    path = d.getVar("CARGO_CRATE_DEST", True)
    path = os.path.join(path, pkg["name"], pkg["vers"])
    bb.utils.mkdirhier(path)
    shutil.copyfile(cratefile,
                    os.path.join(path, "download"))
}
do_install[postfuncs] += "${@base_conditional('CREATE_LOCAL_CARGO_INDEX', '1', 'do_cargo_publish_registry', '', d)}"

# All but the most simple projects will need to override this.
cargo_do_install () {
	local have_installed=false

	pushd "${CARGO_TARGET_DIR}/${CARGO_TARGET_SUBDIR}"
	for tgt in *; do
		if [[ $tgt == *.so ]]; then
			install -D -m755 "$tgt" "${D}${rustlibdir}/$tgt"
			have_installed=true
		elif [[ $tgt == *.rlib ]]; then
			install -D -m644 "$tgt" "${D}${rustlibdir}/$tgt"
			have_installed=true
		elif [ -f "$tgt" ] && [ -x "$tgt" ]; then
			install -D -m755 "$tgt" "${D}${bindir}/$tgt"
			have_installed=true
		fi
	done
	popd

	if ! $have_installed; then
		die "Did not find anything to install"
	fi
}

FILES_${PN}-dev += "${CARGO_INDEX_DIR} ${CARGO_CRATE_DIR}"

EXPORT_FUNCTIONS do_compile do_install do_configure
