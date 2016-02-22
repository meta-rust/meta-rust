INHIBIT_CARGO_DEP = "1"

inherit cargo
inherit patch
inherit rust-installer

SUMMARY = "Cargo downloads your Rust project's dependencies and builds your project"
HOMEPAGE = "http://crates.io"
SECTION = "devel"
LICENSE = "MIT | Apache-2.0"

DEPENDS = "openssl zlib libgit2 curl ca-certificates libssh2"

SRC_URI = "\
	http://static-rust-lang-org.s3.amazonaws.com/cargo-dist/${CARGO_SNAPSHOT} \
"

B = "${S}"

PACKAGECONFIG ??= ""

# Note: this does not appear to work very well due to our use of bitbake triples
# & rust's use of cooked triples
PACKAGECONFIG[rust-snapshot] = "--local-rust-root=${B}/rustc"

# Used in libgit2-sys's build.rs, needed for pkg-config to be used
export LIBGIT2_SYS_USE_PKG_CONFIG = "1"

do_configure () {
	${@bb.utils.contains('PACKAGECONFIG', 'rust-snapshot', '${S}/.travis.install.deps.sh', ':', d)}

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

	# cargo downloads a cargo snapshot to build itself using cargo, we need
	# to override it's arch info.
	cargo_do_configure
}

do_compile () {
	oe_cargo_fix_env

	rm -rf target/snapshot
	mkdir -p target
	cp -R ${WORKDIR}/$(basename ${CARGO_SNAPSHOT} .tar.gz)/cargo target/snapshot

	oe_runmake ARGS="--verbose"
}

do_install () {
	oe_runmake DESTDIR="${D}" install
}

BBCLASSEXTEND = "native"
