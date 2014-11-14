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

export RUST_TARGET_PATH="${WORKDIR}/targets/"

## arm-unknown-linux-gnueabihf
DATA_LAYOUT[arm] = "e-p:32:32:32\
                      -i1:8:8-i8:8:8-i16:16:16-i32:32:32-i64:64:64\
                      -f32:32:32-f64:64:64\
                      -v64:64:64-v128:64:128\
                      -a0:0:64-n32"
LLVM_TARGET[arm] = "arm-unknown-linux-gnueabihf"
TARGET_ENDIAN[arm] = "little"
TARGET_WORD_SIZE[arm] = "32"
FEATURES[arm] = "+v6,+vfp2"

## x86_64-unknown-linux-gnu
DATA_LAYOUT[x86_64] = "e-p:64:64:64-i1:8:8-i8:8:8-i16:16:16-i32:32:32-i64:64:64-\
                      f32:32:32-f64:64:64-v64:64:64-v128:128:128-a0:0:64-\
                      s0:64:64-f80:128:128-n8:16:32:64-S128"
LLVM_TARGET[x86_64] = "x86_64-unknown-linux-gnu"
TARGET_ENDIAN[x86_64] = "little"
TARGET_WORD_SIZE[x86_64] = "64"
PRE_LINK_ARGS[x86_64] = "-m64"

python rust_gen_targets () {


}

# Generates a config file suitable for use as a compiler-and-runtime-build-time
# target specification (distinct from those target specifications used by
# `rustc --target`)
#
# Designed to operate where $1={host,target,build}, and creates targets for
# these using our triples in *_SYS.
rust_gen_mk_cfg () {

	deref() {
		eval echo "\$$1"
	}

	ARCH="$(deref $u_ARCH)"

	local u=`echo $1 | tr '[:lower:]' '[:upper:]'`
	local sys=$(deref ${u}_SYS)
	local rust_base_sys=$(deref RUST_BASE_${u}_SYS)
	local p="${S}/mk/cfg/"

	if [ -z "$sys" ]; then
		bbnote "Rust: no SYS for $u"
		return
	fi
	if [ -z "$rust_base_sys" ]; then
		bbfatal "Rust: no RUST_BUILD_SYS for $u (sys=$sys)"
	fi

	if ! [ -e "$p$rust_base_sys" ]; then
		bberror "Could not find RUST_BASE_${u}_SYS = ${rust_base_sys}"
		bbfatal "file '$p/$rust_base_sys'"
	fi

	# Use one of the existing configs as our base
	cp  -f "$p$rust_base_sys" "$p$sys"

	# FIXME: right now we assume our targets lack regex special characters
	#        and assumes flags lack regex special chars and ';'

	# 1. Fixup the target name for all variables
	# 2. Blank CROSS_PREFIX (XXX: should we set it to "${CCACHE}${$u_PREFIX}"
	#    and adjust other vars as needed?)
	# 3. Edit in our:
	local bare_cc="$(deref ${u}_PREFIX)gcc"
	local cc="${CCACHE}${bare_cc} $(deref ${u}_CC_ARCH)"
	local cxx="${CCACHE}$(deref ${u}_PREFIX)g++ $(deref ${u}_CC_ARCH)"
	local cpp="$(deref ${u}_PREFIX)gcc $(deref ${u}_CC_ARCH) -E"
	local ar="$(deref ${u}_PREFIX)ar"

	# 4. Append our:
	# FIXME: TOOLCHAIN_OPTIONS are only for TARGET (which is sometimes HOST)
	local c_flags="$(deref ${u}_CC_ARCH)${TOOLCHAIN_OPTIONS} $(deref ${u}_CFLAGS)"
	local cxx_flags="$(deref ${u}_CC_ARCH)${TOOLCHAIN_OPTIONS} $(deref ${u}_CXXFLAGS)"
	local link_flags="${TOOLCHAIN_OPTIONS} $(deref ${u}_LD_ARCH)"

	sed -i \
		-e "s/${rust_base_sys}/$sys/g" \
		\
		-e "s/^CROSS_PREFIX_${sys}.*\$//" \
		-e "s/^CC_$sys=.\*\$/CC_$sys := ${cc}/" \
		-e "s/^CXX_$sys=.\*\$/CXX_$sys := ${cxx}/" \
		-e "s/^CPP_$sys=.\*\$/CPP_$sys := ${cpp}/" \
		-e "s/^AR_$sys=.\*\$/AR_$sys := ${ar}/" \
		\
		-e "/^CFG_GCCISH_CFLAGS/ s;\$; ${c_flags};" \
		-e "/^CFG_GCCISH_CXXFLAGS/ s;\$; ${cxx_flags};" \
		-e "/^CFG_GCCISH_LINK_FLAGS/ s;\$; ${link_flags};" \
		\
		"$p/$sys"

	local t="${WORKDIR}/targets/"
	mkdir -p "$t"

	local link_flags_vec='[ "-fPIC" ]'

	cat >"$t$sys" <<-EOF
	{
		"data-layout": "$(deref DATA_LAYOUT__$ARCH)",
		"llvm_target": "${sys}",
		"target_endian": "little",
		"target-word-size": "$(deref TARGET_WORD_SIZE__$ARCH)",
		"arch": "$ARCH",
		"os": "linux",

		"linker": "${bare_cc}",
		"pre_link_args": ${link_flags_vec},
		# post_link_args
		# cpu
		"features": "$(deref FEATURES__$ARCH)",
		"dynamic_linking": true,
		"executables": true,
		"morestack": true,
		# relocation_model
		# ...
		# is_like_windows
		"linker_is_gnu": true,
		"has_rpath": true,
		# no_compiler_rt
		"position_independent_executables": true,
	}
	EOF
}

do_rust_arch_fixup () {
	RUST_BASE_TARGET_SYS="${@rust_triple('${TARGET_ARCH}','${TARGET_VENDOR}','${TARGET_OS}', d)}"
	RUST_BASE_BUILD_SYS="${@rust_triple('${BUILD_ARCH}','${BUILD_VENDOR}','${BUILD_OS}', d)}"
	RUST_BASE_HOST_SYS="${@rust_triple('${HOST_ARCH}','${HOST_VENDOR}','${HOST_OS}', d)}"

	# XXX: these are all hacks around having the variables be shell vars
	# instead of bitbake vars. It probably makes sense to convert this
	# entire mess into python so we don't have to do this.
	HOST_SYS="${HOST_SYS}"
	BUILD_SYS="${BUILD_SYS}"
	TARGET_SYS="${TARGET_SYS}"
	HOST_ARCH="${HOST_ARCH}"
	BUILD_ARCH="${BUILD_ARCH}"
	TARGET_ARCH="${TARGET_ARCH}"


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
		"--target=${TARGET_SYS}"			\
		"--host=${HOST_SYS}"				\
		"--build=${BUILD_SYS}"				\
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

	local td="${D}${datadir}/rust/targets/"
	install -d "$td"
	for tgt in "${WORKDIR}/targets/"* ; do
	    install -m 0644 "$tgt" "$td"
	done
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
