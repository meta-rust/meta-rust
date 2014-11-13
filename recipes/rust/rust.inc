inherit rust

SUMMARY = "Rust compiler and runtime libaries"
HOMEPAGE = "http://www.rust-lang.org"
SECTION = "devel"
LICENSE = "MIT | Apache-2.0"

B = "${WORKDIR}/build"

LIC_FILES_CHKSUM ="\
	file://COPYRIGHT;md5=0e8e4a3b5d8e1c90eb243d406369763a \
"

def rust_triple(arch, vendor, os, d):
    if arch.startswith("arm"):
        vendor = "-unknown"
        if os.endswith("gnueabi"):
            os += bb.utils.contains('TUNE_FEATURES', 'callconvention-hard', 'hf', '', d)
    elif arch.startswith("x86_64"):
        vendor = "-unknown"
        if os == "linux":
            os = "linux-gnu"
    return arch + vendor + '-' + os

RUST_TARGET_SYS = "${@rust_triple('${TARGET_ARCH}','${TARGET_VENDOR}','${TARGET_OS}', d)}"
RUST_BUILD_SYS = "${@rust_triple('${BUILD_ARCH}','${BUILD_VENDOR}','${BUILD_OS}', d)}"
RUST_HOST_SYS = "${@rust_triple('${HOST_ARCH}','${HOST_VENDOR}','${HOST_OS}', d)}"

deref() {
	eval echo "\$$1"
}

strip_flags () {
	# from cmake.bbclass
	sed 's/^\([^ ]*\).*/\1/'
}

# Generates a config file suitable for use as a compiler-and-runtime-build-time
# target specification (distinct from those target specifications used by
# `rustc --target`)
# 
# Designed to operate where $1={host,target,build}, and creates targets named
# 'host', 'target', and 'build' that correspond to these.
rust_gen_mk_cfg () {
	local u=`echo $1 | tr '[:lower:]' '[:upper:]'`
	local sys=$(deref $u_SYS)
	local rust_sys=$(deref RUST_$u_SYS)
	local p="${S}/mk/cfg/"
	if [ -z "$sys" ]; then
		bbnote "Rust: no SYS for $u"
		return
	fi

	if [ -z "$rust_sys" ]; then
		bbfatal "Rust: no RUST_SYS for $u (sys=$sys)"
	fi

	if ! [ -e "$p/$rust_sys" ]; then
		bbfatal "Could not find RUST_$u_SYS = $rust_sys in file '$p/$rust_sys'"
	fi

	if [ -e "$p/$1" ]; then
		bbfatal "Rust config spec already exists: '$p/$1'"
	fi

	# Use one of the existing configs as our base
	cp "$p/$rust_sys" "$p/$1"

	# FIXME: right now we assume our targets lack regex special characters

	# Fixup the target name for all variables
	# Edit in our:
	# - CROSS_PREFIX (blank it)
	# - CC
	local cc="`echo $(deref $u_CC) | strip_flags`"
	# - CXX (from cmake.bbclass)
	local cxx="`echo $(deref $u_CXX) | strip_flags`"
	# - CPP
	local cpp="$cc -E"
	# - AR
	local ar="$(deref $u_AR)"
	# Append our:
	# - CFLAGS
	local c_flags="$(deref $u_CC_ARCH)${TOOLCHAIN_OPTIONS} $(deref $u_CFLAGS)"
	# - CXXFLAGS
	local cxx_flags="$(deref $u_CC_ARCH)${TOOLCHAIN_OPTIONS} $(deref $u_CXXFLAGS)"
	# - LINK_FLAGS
	local link_flags="${TOOLCHAIN_OPTIONS} ${HOST_LD_ARCH}"

	sed -i \
		-e "s/$rust_sys/$1/" \
		\
		-e "s/^CROSS_PREFIX_$1.*\$//gc" \
		-e "s/^CC_$1=.*\$/CC_$1 := ${cc}/" \
		-e "s/^CXX_$1=.*\$/CXX_$1 := ${cxx}/" \
		-e "s/^CPP_$1=.*\$/CPP_$1 := ${cpp}/" \
		-e "s/^AR_$1=.*\$/AR_$1 := ${ar}/" \
		\
		-e "/^CFG_GCCISH_CFLAGS/ s/$/ ${c_flags}/" \
		-e "/^CFG_GCCISH_CXXFLAGS/ s/$/ ${cxx_flags}/" \
		-e "/^CFG_GCCISH_LINK_FLAGS/ s/$/ ${link_flags}/" \
		\
		"$p/$1"
}

do_rust_arch_fixup () {
	RUST_HOST_SYS="${RUST_HOST_SYS}"
	RUST_BUILD_SYS="${RUST_BUILD_SYS}"
	RUST_TARGET_SYS="${RUST_TARGET_SYS}"
	rust_gen_mk_cfg host
	rust_gen_mk_cfg build
	rust_gen_mk_cfg target
}
addtask rust_arch_fixup before do_configure after do_patch

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

	# rpath is required otherwise rustc fails to resolve symbols
	${S}/configure						\
		"--enable-rpath"				\
		"--disable-verify-install"			\
		"--prefix=${prefix}"				\
		"--target=target"				\
		"--host=host"					\
		"--build=build"					\
		"--localstatedir=${localstatedir}"		\
		"--sysconfdir=${sysconfdir}"			\
		"--datadir=${datadir}"				\
		"--infodir=${infodir}"				\
		"--mandir=${mandir}"				\
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
	oe_runmake "$@"
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
