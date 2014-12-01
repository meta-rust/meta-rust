inherit cargo
inherit patch

SUMMARY = "Cargo downloads your Rust project's dependencies and builds your project"
HOMEPAGE = "http://crates.io"
SECTION = "devel"
LICENSE = "MIT | Apache-2.0"

DEPENDS = "openssl zlib libgit2 curl ca-certificates"

SRC_URI = "git://github.com/rust-lang/cargo.git;protocol=https;name=cargo"

LIC_FILES_CHKSUM ="\
	file://LICENSE-MIT;md5=362255802eb5aa87810d12ddf3cfedb4 \
	file://LICENSE-APACHE;md5=1836efb2eb779966696f473ee8540542 \
	file://LICENSE-THIRD-PARTY;md5=afbb7ae0aa70c8e437a007314eae5f3b \
"
SRCREV_FORMAT ?= "cargo"
PV .= "+git${SRCPV}"

S = "${WORKDIR}/git"
B = "${S}"

do_configure () {
	"${S}/configure" \
		"--prefix=${prefix}"			\
		"--build=${BUILD_SYS}"			\
		"--host=${HOST_SYS}"			\
		"--target=${TARGET_SYS}"		\
		"--localstatedir=${localstatedir}"	\
		"--sysconfdir=${sysconfdir}"		\
		"--datadir=${datadir}"			\
		"--infodir=${infodir}"			\
		"--mandir=${mandir}"			\
		"--libdir=${libdir}"			\
		|| die "Could not configure cargo"

	# cargo downloads a cargo snapshot to build itself using cargo, we need
	# to override it's arch info.
	oe_cargo_config
}

do_compile () {
	export CC="${RUST_CC}"
	export CFLAGS="${RUST_CFLAGS}"
	oe_runmake ARGS="--verbose"
}

do_install () {
	oe_runmake DESTDIR="${D}" install
}

BBCLASSEXTEND = "native"
