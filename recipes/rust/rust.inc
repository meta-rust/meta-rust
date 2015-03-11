inherit rust
inherit rust-installer

SUMMARY = "Rust compiler and runtime libaries"
HOMEPAGE = "http://www.rust-lang.org"
SECTION = "devel"
LICENSE = "MIT | Apache-2.0"

B = "${WORKDIR}/build"

# Avoid having the default bitbake.conf disable sub-make parallelization
EXTRA_OEMAKE = ""

LIC_FILES_CHKSUM ="\
	file://COPYRIGHT;md5=b1ab5514343f97198b323e33779470a3 \
"

# Controls whether we use the local rust.
# For -native, we set this to "0" by default.
# This avoids us downloading and using the snapshot for every rust build.
## XXX: temporarily disabled while there are breaking changes conditional on
## stage0 (format_args!() change)
USE_LOCAL_RUST ??= "0"

# We generate local targets, and need to be able to locate them
export RUST_TARGET_PATH="${WORKDIR}/targets/"

## arm-unknown-linux-gnueabihf
DATA_LAYOUT[arm] = "e-p:32:32:32-i1:8:8-i8:8:8-i16:16:16-i32:32:32-i64:64:64-f32:32:32-f64:64:64-v64:64:64-v128:64:128-a0:0:64-n32"
LLVM_TARGET[arm] = "arm-unknown-linux-gnueabihf"
TARGET_ENDIAN[arm] = "little"
TARGET_POINTER_WIDTH[arm] = "32"
FEATURES[arm] = "+v6,+vfp2"
PRE_LINK_ARGS[arm] = "-Wl,--as-needed"

## x86_64-unknown-linux-gnu
DATA_LAYOUT[x86_64] = "e-p:64:64:64-i1:8:8-i8:8:8-i16:16:16-i32:32:32-i64:64:64-f32:32:32-f64:64:64-v64:64:64-v128:128:128-a0:0:64-s0:64:64-f80:128:128-n8:16:32:64-S128"
LLVM_TARGET[x86_64] = "x86_64-unknown-linux-gnu"
TARGET_ENDIAN[x86_64] = "little"
TARGET_POINTER_WIDTH[x86_64] = "64"
PRE_LINK_ARGS[x86_64] = "-Wl,--as-needed -m64"

## i686-unknown-linux-gnu
DATA_LAYOUT[i686] = "e-p:32:32-f64:32:64-i64:32:64-f80:32:32-n8:16:32"
LLVM_TARGET[i686] = "i686-unknown-linux-gnu"
TARGET_ENDIAN[i686] = "little"
TARGET_POINTER_WIDTH[i686] = "32"
PRE_LINK_ARGS[i686] = "-Wl,--as-needed -m32"

## XXX: a bit of a hack so qemux86 builds, clone of i686-unknown-linux-gnu above
DATA_LAYOUT[i586] = "e-p:32:32-f64:32:64-i64:32:64-f80:32:32-n8:16:32"
LLVM_TARGET[i586] = "i586-unknown-linux-gnu"
TARGET_ENDIAN[i586] = "little"
TARGET_POINTER_WIDTH[i586] = "32"
PRE_LINK_ARGS[i586] = "-Wl,--as-needed -m32"

# XXX: BITBAKE-BUG: *_PRE_LINK_ARGS used to be set via function invocation, but
# that caused bitbake to error on users of these variables without any
# backtrace or error message other than "failed" (of some form or another).
# Probably an issue with bitbake attempting to track variable users and us
# having too many dynamic variable names.
#
# enable-new-dtags causes rpaths to be inserted as DT_RUNPATH (as well as
# DT_RPATH), which lets LD_LIBRARY_PATH override them
#
# rust appears to use absolute rpath's instead of relative ones, pass in some
# relative ones so things work a bit better
#
# XXX: may need to restrict the -rpath flags to only BUILD & HOST
RELATIVE_LIB_FROM_BIN = "${@os.path.relpath('${libdir}', '${bindir}')}"
RPATH_LDFLAGS = "-Wl,--enable-new-dtags"
TARGET_PRE_LINK_ARGS = "${RPATH_LDFLAGS} ${TARGET_CC_ARCH} ${TOOLCHAIN_OPTIONS}"
BUILD_PRE_LINK_ARGS = "${RPATH_LDFLAGS} ${BUILD_CC_ARCH} ${TOOLCHAIN_OPTIONS}"
HOST_PRE_LINK_ARGS = "${RPATH_LDFLAGS} ${HOST_CC_ARCH} ${TOOLCHAIN_OPTIONS}"

# These LDFLAGS have '-L' options in them. We need these to come last so they
# don't screw up the link order and pull in the wrong rust build/version.
# TODO: may want to strip out all the '-L' flags entirely here
TARGET_POST_LINK_ARGS = "${TARGET_LDFLAGS}"
BUILD_POST_LINK_ARGS = "${BUILD_LDFLAGS}"
HOST_POST_LINK_ARGS = "${HOST_LDFLAGS}"

def arch_for(d, thing):
    return d.getVar('{}_ARCH'.format(thing), True)

def sys_for(d, thing):
    return d.getVar('{}_SYS'.format(thing), True)

def prefix_for(d, thing):
    return d.getVar('{}_PREFIX'.format(thing), True)

## Note: TOOLCHAIN_OPTIONS is set to "" by native.bbclass and cross.bbclass,
## which prevents us from grabbing them when building a cross compiler (native doesn't matter).
## We workaround this in internal-rust-cross.bbclass.
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

# Convert a normal arch (HOST_ARCH, TARGET_ARCH, BUILD_ARCH, etc) to something
# rust's internals won't choke on.
def arch_to_rust_target_arch(arch):
    if arch == "i586" or arch == "i686":
        return "x86"
    else:
        return arch

def as_json(list_):
    a = '['
    for e in list_:
        if type(e) == str:
            a += '"{}",'.format(e)
        else:
            raise Exception
    if len(list_):
        a = a[:-1]
    a += ']'
    return a

def post_link_args_for(d, thing, arch):
    post_link_args = (d.getVar('{}_POST_LINK_ARGS'.format(thing), True) or "").split()
    post_link_args.extend((d.getVarFlag('POST_LINK_ARGS', arch, True) or "").split())
    return post_link_args


def pre_link_args_for(d, thing, arch):
    ldflags = (d.getVar('{}_PRE_LINK_ARGS'.format(thing), True) or "").split()
    ldflags.extend((d.getVarFlag('PRE_LINK_ARGS', arch, True) or "").split())
    return ldflags

def ldflags_for(d, thing, arch):
    a = pre_link_args_for(d, thing, arch)
    a.extend(post_link_args_for(d, thing, arch))
    return a

def rust_gen_target(d, thing, wd):
    arch = arch_for(d, thing)
    sys = sys_for(d, thing)
    prefix = prefix_for(d, thing)
    o = open(wd + sys + '.json', 'w')

    data_layout = d.getVarFlag('DATA_LAYOUT', arch, True)
    if not data_layout:
        bb.utils.fatal("DATA_LAYOUT[{}] required but not set for {}".format(arch, thing))
    llvm_target = d.getVarFlag('LLVM_TARGET', arch, True)
    target_pointer_width = d.getVarFlag('TARGET_POINTER_WIDTH', arch, True)
    endian = d.getVarFlag('TARGET_ENDIAN', arch, True)
    prefix = d.getVar('{}_PREFIX'.format(thing), True)
    ccache = d.getVar('CCACHE', True)
    linker = "{}{}gcc".format(ccache, prefix)
    features = d.getVarFlag('FEATURES', arch, True) or ""

    pre_link_args = pre_link_args_for(d, thing, arch)
    post_link_args = post_link_args_for(d, thing, arch)

    o.write('''{{
         "data-layout": "{}",
         "llvm-target": "{}",
         "target-endian": "{}",
         "target-word-size": "{}",
         "target-pointer-width": "{}",
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
         "pre-link-args": {},
         "post-link-args": {}
    }}'''.format(
        data_layout,
        llvm_target,
        endian,
        target_pointer_width,
        target_pointer_width,
        arch_to_rust_target_arch(arch),
        linker,
        features,
        as_json(pre_link_args),
        as_json(post_link_args),
    ))
    o.close()

python do_rust_gen_targets () {
    wd = d.getVar('WORKDIR', True) + '/targets/'
    try:
        os.makedirs(wd)
    except OSError as e:
        if e.errno != 17:
            raise e
    for thing in ['BUILD', 'HOST', 'TARGET']:
        bb.debug(1, "rust_gen_target for " + thing)
        rust_gen_target(d, thing, wd)
}
addtask rust_gen_targets after do_patch before do_compile

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
    llvm_target = d.getVarFlag('LLVM_TARGET', arch, True)
    ldflags = ' '.join(ldflags_for(d, thing, arch))

    p = d.getVar('S', True) + '/mk/cfg/'

    o = open(p + sys_for(d, thing) + '.mk', 'w')
    i = open(p + rust_base_sys + '.mk', 'r')

    r = subprocess.call(['sed',
        # update all triplets to the new one
        '-e', 's/{}/{}/g'.format(rust_base_sys, sys),

        # Replace tools with our own (CROSS_PREFIX is appended to all tools
        # by rust's build system). We delete and then insert this because not
        # all targets define it.
        '-e', 's/^CROSS_PREFIX_{}.*$//'.format(sys),
        '-e', '2 a CROSS_PREFIX_{} := {}'.format(sys, prefix),
        '-e', 's/^CFG_LLVM_TARGET_.*$//',
        '-e'  '2 a CFG_LLVM_TARGET_{} := {}'.format(sys, llvm_target),
        '-e', 's/^CC_{}=.*$/CC_{} := gcc/'.format(sys, sys),
        '-e', 's/^CXX_{}.*$/CXX_{} := g++/'.format(sys, sys),
        '-e', 's/^CPP_{}.*$/CPP_{} := gcc -E/'.format(sys, sys),
        '-e', 's/^AR_{}.*$/AR_{} := ar/'.format(sys, sys),

        # Append our flags to the existing ones
        '-e', '/^CFG_JEMALLOC_CFLAGS/ s;$; {};'.format(cflags_for(d, thing)),
        '-e', '/^CFG_GCCISH_CFLAGS/ s;$; {};'.format(cflags_for(d, thing)),
        '-e', '/^CFG_GCCISH_CXXFLAGS/ s;$; {};'.format(cxxflags_for(d, thing)),
        '-e', '/^CFG_GCCISH_LINK_FLAGS/ s;$; {};'.format(ldflags),

        # May need to add: CFG_LLC_FLAGS_{}
        ], stdout=o, stdin=i)
    if r:
        raise Exception

python do_rust_arch_fixup () {
    for thing in ['BUILD', 'HOST', 'TARGET']:
        bb.debug(1, "rust_gen_mk_cfg for " + thing)
        rust_gen_mk_cfg(d, thing)
}
addtask rust_arch_fixup before do_configure after do_patch
do_rust_arch_fixup[dirs] = "${S}/mk/cfg"

do_configure () {
	# FIXME: target_prefix vs prefix, see cross.bbclass

	# CFLAGS, LDFLAGS, CXXFLAGS, CPPFLAGS are used by rust's build for a
	# wide range of targets (not just HOST). Yocto's settings for them will
	# be inappropriate, avoid using.
	unset CFLAGS
	unset LDFLAGS
	unset CXXFLAGS
	unset CPPFLAGS

	# FIXME: this path to rustc (via `which rustc`) may not be quite right in the case
	# where we're reinstalling the compiler. May want to try for a real
	# path based on bitbake vars
        # Also will be wrong when relative libdir and/or bindir aren't 'bin' and 'lib'.
        local_maybe_enable=disable
        local_rust_root=/not/set/do/not/use
        if which rustc >/dev/null 2>&1; then
            local_rustc=$(which rustc)
            if [ -n "$local_rustc" ]; then
                local_rust_root=$(dirname $(dirname $local_rustc))
                if [ -e "$local_rust_root/bin/rustc" ]; then
                    local_maybe_enable=enable
                fi
            fi
        fi

	# - rpath is required otherwise rustc fails to resolve symbols
        # - submodule management is done by bitbake's fetching
	${S}/configure					\
		"--enable-rpath"			\
		"--disable-verify-install"		\
		"--disable-docs"			\
		"--disable-manage-submodules"           \
		"--disable-debug"			\
                "--disable-ldconfig"                    \
		"--enable-optimize"			\
		"--enable-optimize-cxx"			\
		"--enable-optimize-llvm"		\
		"--enable-optimize-tests"		\
		"--prefix=${prefix}"			\
		"--target=${TARGET_SYS}"		\
		"--host=${HOST_SYS}"			\
		"--build=${BUILD_SYS}"			\
		"--localstatedir=${localstatedir}"	\
		"--sysconfdir=${sysconfdir}"		\
		"--datadir=${datadir}"			\
		"--infodir=${infodir}"			\
		"--mandir=${mandir}"			\
		"--libdir=${libdir}"			\
		"--bindir=${bindir}"			\
		${@base_conditional('USE_LOCAL_RUST', '1', '--$local_maybe_enable-local-rust --local-rust-root=$local_rust_root', '--local-rust-root=/not/a/dir', d)} \
		${EXTRA_OECONF}
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

	oe_runmake "VERBOSE=1" "$@"
}

do_compile () {
	rust_runmake
}

rust_do_install () {
	rust_runmake DESTDIR="${D}" install

        # Rust's install.sh doesn't mark executables as executable because
        # we're using a custom bindir, do it ourselves.
        chmod +x "${D}/${bindir}/rustc"
        chmod +x "${D}/${bindir}/rustdoc"
        chmod +x "${D}/${bindir}/rust-gdb"

        # Install our custom target.json files
	local td="${D}${libdir}/rustlib/"
	install -d "$td"
	for tgt in "${WORKDIR}/targets/"* ; do
	    install -m 0644 "$tgt" "$td"
	done

        ## rust will complain about multiple providers of the runtime libs
        ## (libstd, libsync, etc.) without this.
        (cd "${D}${libdir}" && ln -sf "rustlib/${HOST_SYS}/lib/lib"*.so .)
}

do_install () {
	rust_do_install
}

## {{{ native bits

# Otherwise we'll depend on what we provide
INHIBIT_DEFAULT_RUST_DEPS_class-native = "1"
# We don't need to depend on gcc-native because yocto assumes it exists
PROVIDES_class-native = "virtual/${TARGET_PREFIX}rust"
USE_LOCAL_NATIVE_RUST_class-native ??= "0"
USE_LOCAL_RUST_class-native ?= "${@base_conditional('USE_LOCAL_NATIVE_RUST', '0', '0', '1', d)}"

## }}}

## {{{ cross bits

# Otherwise we'll depend on what we provide
INHIBIT_DEFAULT_RUST_DEPS_class-cross = "1"
DEPENDS_class-cross += "rust-native"
PROVIDES_class-cross = "virtual/${TARGET_PREFIX}rust"
PN_class-cross = "rust-cross-${TARGET_ARCH}"

HOST_PRE_LINK_ARGS_append_class-cross = " -Wl,-rpath=${libdir}"
BUILD_PRE_LINK_ARGS_append_class-cross = " -Wl,-rpath=${libdir}"

# We need the same thing for the calls to the compiler when building the runtime crap
TARGET_CC_ARCH_append_class-cross = " --sysroot=${STAGING_DIR_TARGET}"

# cross.bbclass is "helpful" and overrides our do_install. Tell it not to.
do_install_class-cross () {
	rust_do_install
}

## }}}

BBCLASSEXTEND = "cross native"

# FIXME: use FILES to create a -runtime (not -native) package
# $PREFIX/lib/rustlib/`rust_triple`/lib/* contains the runtime libraries (and rlibs)
# Need to copy the *.so files to the appropriate target path
# cp $prefix/lib/rustlib/`rust_triple "${TARGET_ARCH}" "${TARGET_VENDOR}" "${TARGET_OS}"`/lib/*.so ${target_libdir}/

## This is a hack to have -cross provide -native, which doesn't quite work
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
