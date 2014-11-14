inherit rust

SUMMARY = "Rust compiler and runtime libaries"
HOMEPAGE = "http://www.rust-lang.org"
SECTION = "devel"
LICENSE = "MIT | Apache-2.0"

B = "${WORKDIR}/build"

LIC_FILES_CHKSUM ="\
	file://COPYRIGHT;md5=0e8e4a3b5d8e1c90eb243d406369763a \
"

export RUST_TARGET_PATH="${WORKDIR}/targets/"

## arm-unknown-linux-gnueabihf
DATA_LAYOUT[arm] = "e-p:32:32:32-i1:8:8-i8:8:8-i16:16:16-i32:32:32-i64:64:64-f32:32:32-f64:64:64-v64:64:64-v128:64:128-a0:0:64-n32"
LLVM_TARGET[arm] = "arm-unknown-linux-gnueabihf"
TARGET_ENDIAN[arm] = "little"
TARGET_WORD_SIZE[arm] = "32"
FEATURES[arm] = "+v6,+vfp2"
PRE_LINK_ARGS[arm] = "-Wl,--as-needed"

## x86_64-unknown-linux-gnu
DATA_LAYOUT[x86_64] = "e-p:64:64:64-i1:8:8-i8:8:8-i16:16:16-i32:32:32-i64:64:64-f32:32:32-f64:64:64-v64:64:64-v128:128:128-a0:0:64-s0:64:64-f80:128:128-n8:16:32:64-S128"
LLVM_TARGET[x86_64] = "x86_64-unknown-linux-gnu"
TARGET_ENDIAN[x86_64] = "little"
TARGET_WORD_SIZE[x86_64] = "64"
PRE_LINK_ARGS[x86_64] = "-m64 -Wl,--as-needed"

def ldflags_for(d, thing):
    cc_arch = d.getVar('{}_CC_ARCH'.format(thing), True) or ""
    tc = d.getVar('TOOLCHAIN_OPTIONS', True) or ""
    ldflags = d.getVar('{}_LDFLAGS'.format(thing), True) or ""
    return tc.split() + ldflags.split() + cc_arch.split()

def arch_for(d, thing):
    return d.getVar('{}_ARCH'.format(thing), True)

def sys_for(d, thing):
    return d.getVar('{}_SYS'.format(thing), True)

def prefix_for(d, thing):
    return d.getVar('{}_PREFIX'.format(thing), True)

## FIXME: TOOLCHAIN_OPTIONS is set to "" by native.bbclass and cross.bbclass,
## which prevents us from grabbing them when building a cross compiler (native doesn't matter).
def cflags_for(d, thing):
    cc_arch = d.getVar('{}_CC_ARCH'.format(thing), True) or ""
    flags = d.getVar('{}_CFLAGS'.format(thing), True) or ""
    tc = d.getVar('TOOLCHAIN_OPTIONS', True) or ""
    return ' '.join([cc_arch, flags, tc])

def cxxflags_for(d, thing):
    cc_arch = d.getVar('{}_CC_ARCH'.format(thing), True) or ""
    flags = d.getVar('{}_CXXFLAGS'.format(thing), True) or ""
    tc = d.getVar('TOOLCHAIN_OPTIONS', True) or ""
    return ' '.join([cc_arch, flags, tc])

def as_json(list_):
    a = '['
    for e in list_:
        if type(e) == str:
            a += '"{}",'.format(e)
        else:
            raise Exception
    if len(e):
        a = a[:-1]
    a += ']'
    return a

def rust_gen_target(d, thing, wd):
     arch = arch_for(d, thing)
     ldflags = ldflags_for(d, thing)
     sys = sys_for(d, thing)
     prefix = prefix_for(d, thing)
     o = open(wd + sys + '.json', 'w')

     data_layout = d.getVarFlag('DATA_LAYOUT', arch, True)
     llvm_target = d.getVarFlag('LLVM_TARGET', arch, True)
     target_word_size = d.getVarFlag('TARGET_WORD_SIZE', arch, True)
     prefix = d.getVar('{}_PREFIX'.format(thing), True)
     ccache = d.getVar('CCACHE', True)
     linker = "{}{}gcc".format(ccache, prefix)
     features = d.getVarFlag('FEATURES', arch, True) or ""

     pre_link_args = (d.getVarFlag('PRE_LINK_ARGS', arch, True) or "").split()

     o.write('''{{
          "data-layout": "{}",
          "llvm-target": "{}",
          "target-endian": "little",
          "target-word-size": "{}",
          "arch": "{}",
          "os": "linux",
          "linker": "{}",
          "features": "{}",
          "dynamic-linking": true,
          "executables": true,
          "morestack": true,
          "linker-is-gnu": true,
          "has-rpath": true,
          "position-independent-executables": true,
          "pre-link-args": {}
     }}'''.format(
               data_layout,
               llvm_target,
               target_word_size,
               arch,
               linker,
               features,
               as_json(pre_link_args)
     ))
     o.close()

python do_rust_gen_targets () {
     import os
     wd = d.getVar('WORKDIR', True) + '/targets/'
     try:
         os.makedirs(wd)
     except OSError as e:
         if e.errno != 17:
            raise e

     for thing in ['HOST', 'BUILD', 'TARGET']:
        rust_gen_target(d, thing, wd)
}
addtask do_rust_gen_targets after do_patch before do_compile

def rust_base_triple(d, thing):
    '''
    Mangle bitbake's *_SYS into something that rust might support (see
    rust/mk/cfg/* for a list)
    '''

    arch = d.getVar('{}_ARCH'.format(thing), True)
    vendor = d.getVar('{}_VENDOR'.format(thing), True)
    os = d.getVar('{}_OS'.format(thing), True)

    if arch.startswith("arm"):
        vendor = "-unknown"
        if os.endswith("gnueabi"):
            os += bb.utils.contains('TUNE_FEATURES', 'callconvention-hard', 'hf', '', d)
    elif arch.startswith("x86_64"):
        vendor = "-unknown"
        if os == "linux":
            os = "linux-gnu"
    return arch + vendor + '-' + os

def rust_gen_mk_cfg(d, thing):
    ''''
    Rust's build system adds support for new archs via 2 things:
     1. a file in mk/cfg which defines how the runtime libraries are built
     2. and rustc arch definition either built into the compiler or supplied as a .json file

    This generates a new #1 for the given 'thing' (one of HOST, TARGET, BUILD)
    using a "similar" config that rust already supplies as a template.

    Note that the configure process also depends on the existence of #1, so we
    have to run this before do_configure
    '''

    import shutil, subprocess
    rust_base_sys = rust_base_triple(d, thing)
    arch = arch_for(d, thing)
    sys = sys_for(d, thing)
    prefix = prefix_for(d, thing)

    p = d.getVar('S', True) + '/mk/cfg/'

    o = open(p + sys_for(d, thing), 'w')

    r = subprocess.call(['sed',
        # update all triplets to the new one
        '-e', 's/{}/{}/g'.format(rust_base_sys, sys),

        # Replace tools with our own (CROSS_PREFIX is appended to all tools
        # by rust's build system)
        '-e', 's/^CROSS_PREFIX_{}.*$/CROSS_PREFIX_{} := {}/'.format(sys, sys, prefix),
        '-e', 's/^CC_{}=.*$/CC_{} := gcc/'.format(sys, sys),
        '-e', 's/^CXX_{}.*$/CXX_{} := g++/'.format(sys, sys),
        '-e', 's/^CPP_{}.*$/CPP_{} := gcc -E/'.format(sys, sys),
        '-e', 's/^AR_{}.*$/AR_{} := ar/'.format(sys, sys),

        # Append our flags to the existing ones
        '-e', '/^CFG_GCCISH_CFLAGS/ s;$; {};'.format(cflags_for(d, thing)),
        '-e', '/^CFG_GCCISH_CXXFLAGS/ s;$; {};'.format(cxxflags_for(d, thing)),
        '-e', '/^CFG_GCCISH_LINK_FLAGS/ s;$; {};'.format(" ".join(ldflags_for(d, thing))),

        p + rust_base_sys
        ], stdout=o)
    if r:
        raise Exception

python do_rust_arch_fixup () {
    for thing in ['HOST', 'BUILD', 'TARGET']:
        rust_gen_mk_cfg(d, thing)
}
addtask do_rust_arch_fixup before do_configure after do_patch

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
	# wide range of targets (not just TARGET). Yocto's settings for them will
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
