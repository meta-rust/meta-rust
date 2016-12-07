inherit cargo
inherit patch

SUMMARY = "Cargo downloads your Rust project's dependencies and builds your project"
HOMEPAGE = "http://crates.io"
SECTION = "devel"
LICENSE = "MIT | Apache-2.0"

DEPENDS = "openssl zlib libgit2 curl ca-certificates libssh2"

SRC_URI = "\
	http://static-rust-lang-org.s3.amazonaws.com/cargo-dist/${CARGO_SNAPSHOT} \
"

B = "${S}"

# Used in libgit2-sys's build.rs, needed for pkg-config to be used
export LIBGIT2_SYS_USE_PKG_CONFIG = "1"

# cargo's configure doesn't recognize --disable-static, so remove it.
DISABLE_STATIC = ""

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
		"--disable-verify-install"		\
		${EXTRA_OECONF} \
		|| die "Could not configure cargo"

	cargo_do_configure
}

do_compile () {
	oe_cargo_fix_env

	rm -rf target/snapshot
	mkdir -p target
	cp -R ${WORKDIR}/cargo-nightly-x86_64-unknown-linux-gnu/cargo target/snapshot

	oe_runmake VERBOSE=1
}

do_install () {
	oe_runmake prepare-image-${TARGET_SYS} IMGDIR_${TARGET_SYS}="${D}${prefix}"
}

BBCLASSEXTEND = "native"
