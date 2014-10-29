inherit rust

SUMMARY = "Rust compiler and runtime libaries"
HOMEPAGE = "http://www.rust-lang.org"
SECTION = "devel"
LICENSE = "MIT | Apache-2.0"

B = "${WORKDIR}/build"

LIC_FILES_CHKSUM ="\
	file://COPYRIGHT;md5=0e8e4a3b5d8e1c90eb243d406369763a \
"

do_configure () {
	# FIXME: allow --enable-local-rust
	# FIXME: target_prefix vs prefix, see cross.bbclass
	# FIXME: handle non-native builds

	# CFLAGS, LDFLAGS, CXXFLAGS, CPPFLAGS are used by rust's build for a
	# wide range of targets (not just HOST). Yocto's settings for them will
	# be inappropriate, avoid using.
	unset CFLAGS
	unset LDFLAGS
	unset CXXFLAGS
	unset CPPFLAGS

	# XXX: rpath is required otherwise rustc fails to resolve symbols

	${S}/configure						\
		"--enable-rpath"				\
		"--disable-verify-install"			\
		"--prefix=${prefix}"				\
		"--target=${RUST_TARGET_SYS}"			\
		"--localstatedir=${localstatedir}"		\
		"--sysconfdir=${sysconfdir}"			\
		"--datadir=${datadir}"				\
		"--infodir=${infodir}"				\
		"--mandir=${mandir}"				\
		"--build=${RUST_BUILD_SYS}"			\
		"--host=${RUST_HOST_SYS}"			\
		"--libdir=${libdir}"


}

rust_runmake () {
	echo "COMPILE ${PN}" "$@"
	env

	# CFLAGS, LDFLAGS, CXXFLAGS, CPPFLAGS are used by rust's build for a
	# wide range of targets (not just HOST). Yocto's settings for them will
	# be inappropriate, avoid using.
	unset CFLAGS
	unset LDFLAGS
	unset CXXFLAGS
	unset CPPFLAGS

	# FIXME: this only works if RT != RH. For RT == RH, we need to add
	# additional targets to platform.mk and patch rust to understand the
	# new triples (so it can find runtime libraries).

	# Note: these variable names include '-', so we can't supply them via
	# shell exports
	oe_runmake								\
		CROSS_PREFIX_${RUST_TARGET_SYS}=				\
		CC_${rt}="${CCACHE}${TARGET_PREFIX}gcc ${TARGET_CC_ARCH}"	\
		CXX_${rt}="${CCACHE}${TARGET_PREFIX}g++ ${TARGET_CC_ARCH}"	\
		CPP_${rt}="${TARGET_PREFIX}gcc ${TARGET_CC_ARCH} -E"		\
		AR_${rt}="${TARGET_PREFIX}ar"					\
		\
		CROSS_PREFIX_${ROST_HOST_SYS}=					\
		CC_${rh}="${CCACHE}${HOST_PREFIX}gcc ${HOST_CC_ARCH}"		\
		CXX_${rh}="${CCACHE}${HOST_PREFIX}g++ ${HOST_CC_ARCH}"		\
		CPP_${rh}="${HOST_PREFIX}gcc ${HOST_CC_ARCH} -E"		\
		AR_${rh}="${HOST_PREFIX}ar"					\
		\
		CFG_CFLAGS_${RUST_TARGET_SYS}="${TARGET_CFLAGS}"		\
		CFG_LDFLAGS_${RUST_TARGET_SYS}="${TARGET_LDFLAGS}"		\
		CFG_CFLAGS_${RUST_HOST_SYS}="${HOST_CFLAGS}"			\
		CFG_LDFLAGS_${RUST_HOST_SYS}="${HOST_LDFLAGS}"			\
		\
		"$@"
}

do_compile () {
	rust_runmake
}

do_install () {
	rust_runmake DESTDIR="${D}" install
}

# FIXME: use FILES to create a -runtime (not -native) package
# $PREFIX/lib/rustlib/`rust_triple`/lib/* contains the runtime libraries (and rlibs)
# Need to copy the *.so files to the appropriate target path
# cp $prefix/lib/rustlib/`rust_triple "${TARGET_ARCH}" "${TARGET_VENDOR}" "${TARGET_OS}"`/lib/*.so ${target_libdir}/

# cross-canadian: llvm configure fails for host while attempting to build host-only llvm
BBCLASSEXTEND = "cross native"

#python cross_virtclass_provides_native_handler () {
#	classextend = e.data.getVar('BBCLASSEXTEND', True) or ""
#	if "cross" not in classextend:
#		return
#	pn = e.data.getVar("PN", True)
#	if not pn.endswith("-cross"):
#		return
#	e.data.prependVar("PROVIDES", "rust-native ")
#}
#addhandler cross_virtclass_provides_native_handler
#cross_virtclass_provides_native_handler[eventmask] = "bb.event.RecipePreFinalise"
