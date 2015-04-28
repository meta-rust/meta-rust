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
	git://github.com/rust-lang/cargo.git;protocol=https;name=cargo \
	git://github.com/rust-lang/rust-installer.git;protocol=https;name=rust-installer;destsuffix=git/src/rust-installer \
	http://static-rust-lang-org.s3.amazonaws.com/cargo-dist/2015-04-02/cargo-nightly-x86_64-unknown-linux-gnu.tar.gz \
"

SRC_URI[md5sum] = "3d62194d02a9088cd8aae379e9498134"
SRC_URI[sha256sum] = "16b6338ba2942989693984ba4dbd057c2801e8805e6da8fa7b781b00e722d117"

LIC_FILES_CHKSUM ="\
	file://LICENSE-MIT;md5=362255802eb5aa87810d12ddf3cfedb4 \
	file://LICENSE-APACHE;md5=1836efb2eb779966696f473ee8540542 \
	file://LICENSE-THIRD-PARTY;md5=afbb7ae0aa70c8e437a007314eae5f3b \
"
SRCREV_FORMAT = "cargo_rust-installer"
PV .= "+git${SRCPV}"

S = "${WORKDIR}/git"
B = "${S}"

PACKAGECONFIG ??= ""

# Note: this does not appear to work very well due to our use of bitbake triples
# & rust's use of cooked triples
PACKAGECONFIG[rust-snapshot] = "--local-rust-root=${B}/rustc"

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
	cp -R ${WORKDIR}/cargo-nightly-x86_64-unknown-linux-gnu target/snapshot
	export LD_LIBRARY_PATH="${STAGING_LIBDIR_NATIVE}"
	oe_runmake ARGS="--verbose"
}

do_install () {
	oe_runmake DESTDIR="${D}" install
}

BBCLASSEXTEND = "native"
