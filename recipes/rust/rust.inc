# ex: sts=4 et sw=4 ts=8
inherit rust
inherit rust-installer
require rust-shared-source.inc
require rust-snapshot-2015-08-11.inc

LIC_FILES_CHKSUM ="file://COPYRIGHT;md5=eb87dba71cb424233bcce88db3ae2f1a"

SUMMARY = "Rust compiler and runtime libaries"
HOMEPAGE = "http://www.rust-lang.org"
SECTION = "devel"

B = "${WORKDIR}/build"

DEPENDS += "file-native"

# Avoid having the default bitbake.conf disable sub-make parallelization
EXTRA_OEMAKE = ""

PACKAGECONFIG ??= ""

# Controls whether we use the local rust to build.
# By default, we use the rust-snapshot. In some cases (non-supported host
# systems) this may not be possible.  In other cases, it might be desirable
# to have rust-cross built using rust-native.
PACKAGECONFIG[local-rust] = ""

SRC_URI += "${@bb.utils.contains('PACKAGECONFIG', 'local-rust', '', 'https://static.rust-lang.org/stage0-snapshots/${RUST_SNAPSHOT};unpack=0;name=rust-snapshot', d)}"

# We generate local targets, and need to be able to locate them
export RUST_TARGET_PATH="${WORKDIR}/targets/"

export FORCE_CRATE_HASH="${BB_TASKHASH}"

# Right now this is focused on arm-specific tune features.
# We get away with this for now as one can only use x86-64 as the build host
# (not arm).
# Note that TUNE_FEATURES is _always_ refering to the target, so we really
# don't want to use this for the host/build.
def llvm_features_from_tune(d):
    f = []
    feat = d.getVar('TUNE_FEATURES', True)
    if not feat:
        return ""
    feat = frozenset(feat.split())

    if 'vfpv4' in feat:
        f.append("+vfp4")
    if 'vfpv3' in feat:
        f.append("+vfp3")
    if 'vfpv3d16' in feat:
        f.append("+d16")

    if 'vfpv2' in feat or 'vfp' in feat:
        f.append("+vfp2")

    if 'neon' in feat:
        f.append("+neon")

    if 'aarch64' in feat:
        f.append("+v8")

    v7=frozenset(['armv7a', 'armv7r', 'armv7m', 'armv7ve'])
    if not feat.isdisjoint(v7):
        f.append("+v7")
    if 'armv6' in feat:
        f.append("+v6")

    if 'dsp' in feat:
        f.append("+dsp")

    if d.getVar('ARM_THUMB_OPT', True) is "thumb":
        if not feat.isdisjoint(v7):
            f.append("+thumb2")
        f.append("+thumb-mode")

    if 'cortexa5' in feat:
        f.append("+a5")
    if 'cortexa7' in feat:
        f.append("+a7")
    if 'cortexa9' in feat:
        f.append("+a9")
    if 'cortexa15' in feat:
        f.append("+a15")
    if 'cortexa17' in feat:
        f.append("+a17")

    # Seems like it could be infered by the lack of vfp options, but we'll
    # include it anyhow
    if 'soft' in feat:
        f.append("+soft-float")

    return ','.join(f)

## arm-unknown-linux-gnueabihf
DATA_LAYOUT[arm] = "e-p:32:32:32-i1:8:8-i8:8:8-i16:16:16-i32:32:32-i64:64:64-f32:32:32-f64:64:64-v64:64:64-v128:64:128-a0:0:64-n32"
LLVM_TARGET[arm] = "${RUST_TARGET_SYS}"
TARGET_ENDIAN[arm] = "little"
TARGET_POINTER_WIDTH[arm] = "32"
FEATURES[arm] = "+v6,+vfp2"
PRE_LINK_ARGS[arm] = "-Wl,--as-needed"

DATA_LAYOUT[aarch64] = "e-p:64:64:64-i1:8:8-i8:8:8-i16:16:16-i32:32:32-i64:64:64-f32:32:32-f64:64:64-v64:64:64-v128:128:128-a0:0:64-s0:64:64-n32:64-S128"
LLVM_TARGET[aarch64] = "aarch64-unknown-linux-gnu"
TARGET_ENDIAN[aarch64] = "little"
TARGET_POINTER_WIDTH[aarch64] = "64"
PRE_LINK_ARGS[aarch64] = "-Wl,--as-needed"

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

# enable-new-dtags causes rpaths to be inserted as DT_RUNPATH (as well as
# DT_RPATH), which lets LD_LIBRARY_PATH override them
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

TARGET_LLVM_FEATURES = "${@llvm_features_from_tune(d)}"
TARGET_LLVM_FEATURES_class-cross  = "${@llvm_features_from_tune(d)}"

# class-native implies TARGET=HOST, and TUNE_FEATURES only describes the real
# (original) target.
TARGET_LLVM_FEATURES_class-native = ""

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
    objcopy = "{}objcopy".format(prefix)

    features = ""
    if thing is "TARGET":
        features = d.getVar('TARGET_LLVM_FEATURES', True) or ""
    features = features or d.getVarFlag('FEATURES', arch, True) or ""

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
         "objcopy": "{}",
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
        objcopy,
        features,
        as_json(pre_link_args),
        as_json(post_link_args),
    ))
    o.close()

python do_rust_gen_targets () {
    wd = d.getVar('WORKDIR', True) + '/targets/'
    # It is important 'TARGET' is last here so that it overrides our less
    # informed choices for BUILD & HOST if TARGET happens to be the same as
    # either of them.
    for thing in ['BUILD', 'HOST', 'TARGET']:
        bb.debug(1, "rust_gen_target for " + thing)
        rust_gen_target(d, thing, wd)
}
addtask rust_gen_targets after do_patch before do_compile
do_rust_gen_targets[dirs] += "${WORKDIR}/targets"

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
    import subprocess

    rust_base_sys = rust_base_triple(d, thing)
    arch = arch_for(d, thing)
    sys = sys_for(d, thing)
    prefix = prefix_for(d, thing)
    llvm_target = d.getVarFlag('LLVM_TARGET', arch, True)
    ldflags = ' '.join(ldflags_for(d, thing, arch))

    b = d.getVar('WORKDIR', True) + '/mk-cfg/'
    o = open(b + sys_for(d, thing) + '.mk', 'w')
    i = open(d.getVar('S', True) + '/mk/cfg/' + rust_base_sys + '.mk', 'r')

    r = subprocess.call(['sed',
        # update all triplets to the new one
        '-e', 's/{}/{}/g'.format(rust_base_sys, sys),

        # Replace tools with our own (CROSS_PREFIX is appended to all tools
        # by rust's build system). We delete and then insert this because not
        # all targets define it.
        '-e', 's/^CROSS_PREFIX_{}.*$//'.format(sys),
        '-e', '2 a CROSS_PREFIX_{} := {}'.format(sys, prefix),
        '-e', 's/^CFG_LLVM_TARGET_.*$//',
        '-e', '2 a CFG_LLVM_TARGET_{} := {}'.format(sys, llvm_target),
        '-e', 's/^CC_{}=.*$/CC_{} := gcc/'.format(sys, sys),
        '-e', 's/^CXX_{}.*$/CXX_{} := g++/'.format(sys, sys),
        '-e', 's/^CPP_{}.*$/CPP_{} := gcc -E/'.format(sys, sys),
        '-e', 's/^AR_{}.*$/AR_{} := ar/'.format(sys, sys),

        # Some targets don't have LINK even though it is required to build.
        '-e', 's/^LINK_{}.*$//'.format(sys),
        '-e', '2 a LINK_{} := gcc'.format(sys),

        # Append our flags to the existing ones
        '-e', '/^CFG_JEMALLOC_CFLAGS/ s;$; {};'.format(cflags_for(d, thing)),
        '-e', '/^CFG_GCCISH_CFLAGS/ s;$; {};'.format(cflags_for(d, thing)),
        '-e', '/^CFG_GCCISH_CXXFLAGS/ s;$; {};'.format(cxxflags_for(d, thing)),
        '-e', '/^CFG_GCCISH_LINK_FLAGS/ s;$; {};'.format(ldflags),

        # May need to add: CFG_LLC_FLAGS_{}
        ], stdout=o, stdin=i)
    if r:
        raise Exception
    o.write("OBJCOPY_{} := {}objcopy\n".format(sys, prefix))
    o.close()
    i.close()

python do_rust_arch_fixup () {
    for thing in ['BUILD', 'HOST', 'TARGET']:
        bb.debug(1, "rust_gen_mk_cfg for " + thing)
        rust_gen_mk_cfg(d, thing)
}
addtask rust_arch_fixup before do_configure after do_patch
do_rust_arch_fixup[dirs] += "${WORKDIR}/mk-cfg"

llvmdir = "${STAGING_DIR_NATIVE}/${prefix_native}"

do_configure () {
    # Note: when we adjust the generated targets, rust doesn't rebuild (even
    # when it should), so for now we need to remove the build dir to keep
    # things in sync.
    cd "${WORKDIR}"
    rm -rf "${B}/"
    mkdir -p "${B}/"
    cd "${B}"

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
    ${S}/configure                          \
        "--enable-rpath"                    \
        "--disable-docs"                    \
        "--disable-manage-submodules"       \
        "--disable-debug"                   \
        "--enable-debuginfo"                \
        "--enable-optimize"                 \
        "--enable-optimize-cxx"             \
        "--disable-llvm-version-check"      \
        "--llvm-root=${llvmdir}"            \
        "--enable-optimize-tests"           \
        "--prefix=${prefix}"                \
        "--target=${TARGET_SYS}"            \
        "--host=${HOST_SYS}"                \
        "--build=${BUILD_SYS}"              \
        "--localstatedir=${localstatedir}"  \
        "--sysconfdir=${sysconfdir}"        \
        "--datadir=${datadir}"              \
        "--infodir=${infodir}"              \
        "--mandir=${mandir}"                \
        "--libdir=${libdir}"                \
        "--bindir=${bindir}"                \
        "--platform-cfg=${WORKDIR}/mk-cfg/" \
        ${@bb.utils.contains('PACKAGECONFIG', 'local-rust', '--$local_maybe_enable-local-rust --local-rust-root=$local_rust_root', '--local-rust-root=/not/a/dir', d)} \
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
    if ${@bb.utils.contains('PACKAGECONFIG', 'local-rust', 'false', 'true', d)}; then
        mkdir -p dl
        cp -f ${WORKDIR}/${RUST_SNAPSHOT} dl
    fi
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

