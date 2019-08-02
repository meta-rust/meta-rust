SUMMARY = "Cargo, a package manager for Rust."
HOMEPAGE = "https://crates.io"
LICENSE = "MIT | Apache-2.0"
SECTION = "devel"

DEPENDS = "openssl zlib libgit2 curl ca-certificates libssh2"

LIC_FILES_CHKSUM = " \
    file://LICENSE-MIT;md5=b377b220f43d747efdec40d69fcaa69d \
"

SRC_URI += "file://0001-Disable-http2.patch"

S = "${RUSTSRC}/src/tools/cargo"
CARGO_VENDORING_DIRECTORY = "${RUSTSRC}/vendor"

inherit cargo

do_cargo_setup_snapshot () {
	${WORKDIR}/rust-snapshot-components/${CARGO_SNAPSHOT}/install.sh --prefix="${WORKDIR}/${CARGO_SNAPSHOT}" --disable-ldconfig
}

addtask cargo_setup_snapshot after do_unpack before do_configure
do_cargo_setup_snapshot[dirs] += "${WORKDIR}/${CARGO_SNAPSHOT}"

do_compile_prepend () {
	export RUSTC_BOOTSTRAP="1"
}

do_install () {
	install -d "${D}${bindir}"
	install -m 755 "${RUSTSRC}/target/${CARGO_TARGET_SUBDIR}/cargo" "${D}${bindir}"
}

# Needed for pkg-config to be used
export LIBGIT2_SYS_USE_PKG_CONFIG = "1"
export LIBSSH2_SYS_USE_PKG_CONFIG = "1"

BBCLASSEXTEND = "native"

# When building cargo-native we don't have a built cargo to use so we must use
# the snapshot to bootstrap the build of cargo
CARGO_class-native = "${WORKDIR}/${CARGO_SNAPSHOT}/bin/cargo"
