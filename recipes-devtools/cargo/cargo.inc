inherit cargo
inherit patch
inherit rust-installer

SUMMARY = "Cargo downloads your Rust project's dependencies and builds your project"
HOMEPAGE = "http://crates.io"
SECTION = "devel"
LICENSE = "MIT | Apache-2.0"

DEPENDS = "openssl zlib libgit2 curl ca-certificates libssh2"

CARGO_INDEX_COMMIT = "6127fc24b0b6fe73fe4d339817fbf000b9a798a2"

SRC_URI = "\
	http://static-rust-lang-org.s3.amazonaws.com/cargo-dist/${CARGO_SNAPSHOT} \
	crate://crates.io/advapi32-sys/0.1.2 \
	crate://crates.io/bufstream/0.1.1 \
	crate://crates.io/crossbeam/0.2.8 \
	crate://crates.io/docopt/0.6.78 \
	crate://crates.io/env_logger/0.3.2 \
	crate://crates.io/filetime/0.1.10 \
	crate://crates.io/flate2/0.2.13 \
	crate://crates.io/fs2/0.2.3 \
	crate://crates.io/glob/0.2.11 \
	crate://crates.io/hamcrest/0.1.0 \
	crate://crates.io/kernel32-sys/0.2.1 \
	crate://crates.io/libc/0.2.8 \
	crate://crates.io/log/0.3.5 \
	crate://crates.io/num_cpus/0.2.11 \
	crate://crates.io/regex/0.1.58 \
	crate://crates.io/rustc-serialize/0.3.18 \
	crate://crates.io/tar/0.4.5 \
	crate://crates.io/tempdir/0.3.4 \
	crate://crates.io/term/0.4.4 \
	crate://crates.io/toml/0.1.28 \
	crate://crates.io/url/1.1.0 \
	crate://crates.io/winapi/0.2.6 \
	crate://crates.io/semver/0.2.3 \
	crate://crates.io/regex-syntax/0.3.0 \
	crate://crates.io/utf8-ranges/0.1.3 \
	crate://crates.io/gcc/0.3.26 \
	crate://crates.io/unicode-normalization/0.1.2 \
	crate://crates.io/libz-sys/1.0.2 \
	crate://crates.io/rand/0.3.14 \
	crate://crates.io/user32-sys/0.1.2 \
	crate://crates.io/idna/0.1.0 \
	crate://crates.io/strsim/0.3.0 \
	crate://crates.io/matches/0.1.2 \
	crate://crates.io/cmake/0.1.16 \
	crate://crates.io/gdi32-sys/0.1.1 \
	crate://crates.io/bitflags/0.1.1 \
	crate://crates.io/unicode-bidi/0.2.3 \
	crate://crates.io/pkg-config/0.3.8 \
	crate://crates.io/winapi-build/0.1.1 \
	crate://crates.io/memchr/0.1.10 \
	crate://crates.io/pnacl-build-helper/1.4.10 \
	crate://crates.io/nom/1.2.2 \
	crate://crates.io/num/0.1.31 \
	crate://crates.io/uuid/0.2.3 \
	crate://crates.io/aho-corasick/0.5.1 \
	crate://crates.io/libressl-pnacl-sys/2.1.6 \
	crate://crates.io/miniz-sys/0.1.7 \
	crate://crates.io/openssl-sys/0.7.8 \
	crate://crates.io/url/0.5.10 \
	crate-index://crates.io/${CARGO_INDEX_COMMIT} \
"

B = "${S}"

PACKAGECONFIG ??= ""

# Note: this does not appear to work very well due to our use of bitbake triples
# & rust's use of cooked triples
PACKAGECONFIG[rust-snapshot] = "--local-rust-root=${B}/rustc"

# Used in libgit2-sys's build.rs, needed for pkg-config to be used
export LIBGIT2_SYS_USE_PKG_CONFIG = "1"

# cargo's configure doesn't recognize --disable-static, so remove it.
DISABLE_STATIC = ""

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

	cargo_do_configure
}

do_compile () {
	oe_cargo_fix_env

	rm -rf target/snapshot
	mkdir -p target
	cp -R ${WORKDIR}/cargo-nightly-x86_64-unknown-linux-gnu/cargo target/snapshot

	oe_runmake ARGS="--verbose"
}

do_install () {
	oe_runmake DESTDIR="${D}" install
}

BBCLASSEXTEND = "native"
