SUMMARY = "Rust compiler and runtime libaries"
HOMEPAGE = "http://www.rust-lang.org"
SECTION = "devel"
LICENSE = "MIT | Apache-2.0"
LIC_FILES_CHKSUM ="file://COPYRIGHT;md5=43e1f1fb9c0ee3af66693d8c4fecafa8"

inherit rust

SRC_URI = "\
	https://static.rust-lang.org/dist/${RUST_SNAPSHOT}.tar.gz;name=rust-snapshot \
    "

DEPENDS += "file-native"

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

# TARGET_CC_ARCH changes from build/cross/target so it'll do the right thing
# this should go away when https://github.com/rust-lang/rust/pull/31709 is
# stable (1.9.0?)
def llvm_features_from_cc_arch(d):
    f = []
    feat = d.getVar('TARGET_CC_ARCH', True)
    if not feat:
        return ""
    feat = frozenset(feat.split())

    if '-mmmx' in feat:
        f.append("+mmx")
    if '-msse' in feat:
        f.append("+sse")
    if '-msse2' in feat:
        f.append("+sse2")
    if '-msse3' in feat:
        f.append("+sse3")
    if '-mssse3' in feat:
        f.append("+ssse3")
    if '-msse4.1' in feat:
        f.append("+sse4.1")
    if '-msse4.2' in feat:
        f.append("+sse4.2")
    if '-msse4a' in feat:
        f.append("+sse4a")
    if '-mavx' in feat:
        f.append("+avx")
    if '-mavx2' in feat:
        f.append("+avx2")

    return ','.join(f)

## arm-unknown-linux-gnueabihf
DATA_LAYOUT[arm] = "e-m:e-p:32:32-i64:64-v128:64:128-a:0:32-n32-S64"
LLVM_TARGET[arm] = "${RUST_TARGET_SYS}"
TARGET_ENDIAN[arm] = "little"
TARGET_POINTER_WIDTH[arm] = "32"
FEATURES[arm] = "+v6,+vfp2"

## aarch64-unknown-linux-gnu
DATA_LAYOUT[aarch64] = "e-m:e-i8:8:32-i16:16:32-i64:64-i128:128-n32:64-S128"
LLVM_TARGET[aarch64] = "aarch64-unknown-linux-gnu"
TARGET_ENDIAN[aarch64] = "little"
TARGET_POINTER_WIDTH[aarch64] = "64"

## x86_64-unknown-linux-gnu
DATA_LAYOUT[x86_64] = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
LLVM_TARGET[x86_64] = "x86_64-unknown-linux-gnu"
TARGET_ENDIAN[x86_64] = "little"
TARGET_POINTER_WIDTH[x86_64] = "64"

## i686-unknown-linux-gnu
DATA_LAYOUT[i686] = "e-m:e-p:32:32-f64:32:64-f80:32-n8:16:32-S128"
LLVM_TARGET[i686] = "i686-unknown-linux-gnu"
TARGET_ENDIAN[i686] = "little"
TARGET_POINTER_WIDTH[i686] = "32"

## XXX: a bit of a hack so qemux86 builds, clone of i686-unknown-linux-gnu above
DATA_LAYOUT[i586] = "e-m:e-p:32:32-f64:32:64-f80:32-n8:16:32-S128"
LLVM_TARGET[i586] = "i586-unknown-linux-gnu"
TARGET_ENDIAN[i586] = "little"
TARGET_POINTER_WIDTH[i586] = "32"

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

# generates our target CPU value
def llvm_cpu(d):
    cpu = d.getVar('PACKAGE_ARCH', True)
    target = d.getVar('TRANSLATED_TARGET_ARCH', True)

    trans = {}
    trans['corei7-64'] = "corei7"
    trans['core2-32'] = "core2"
    trans['x86-64'] = "x86-64"
    trans['i686'] = "i686"
    trans['i586'] = "i586"

    try:
        return trans[cpu]
    except:
        return trans.get(target, "generic")

TARGET_LLVM_CPU="${@llvm_cpu(d)}"
TARGET_LLVM_FEATURES = "${@llvm_features_from_tune(d)} ${@llvm_features_from_cc_arch(d)}"

# class-native implies TARGET=HOST, and TUNE_FEATURES only describes the real
# (original) target.
TARGET_LLVM_FEATURES_class-native = "${@llvm_features_from_cc_arch(d)}"

def rust_gen_target(d, thing, wd):
    import json
    arch = arch_for(d, thing)
    sys = sys_for(d, thing)
    prefix = prefix_for(d, thing)

    features = ""
    cpu = "generic"
    if thing is "TARGET":
        features = d.getVar('TARGET_LLVM_FEATURES', True) or ""
        cpu = d.getVar('TARGET_LLVM_CPU', True)
    features = features or d.getVarFlag('FEATURES', arch, True) or ""
    features = features.strip()

    # build tspec
    tspec = {}
    tspec['llvm-target'] = d.getVarFlag('LLVM_TARGET', arch, True)
    tspec['data-layout'] = d.getVarFlag('DATA_LAYOUT', arch, True)
    tspec['target-pointer-width'] = d.getVarFlag('TARGET_POINTER_WIDTH', arch, True)
    tspec['target-word-size'] = tspec['target-pointer-width']
    tspec['target-endian'] = d.getVarFlag('TARGET_ENDIAN', arch, True)
    tspec['arch'] = arch_to_rust_target_arch(arch)
    tspec['os'] = "linux"
    tspec['env'] = "gnu"
    tspec['linker'] = "{}{}gcc".format(d.getVar('CCACHE', True), prefix)
    tspec['objcopy'] = "{}objcopy".format(prefix)
    tspec['ar'] = "{}ar".format(prefix)
    tspec['cpu'] = cpu
    if features is not "":
        tspec['features'] = features
    tspec['dynamic-linking'] = True
    tspec['executables'] = True
    tspec['morestack'] = True
    tspec['linker-is-gnu'] = True
    tspec['has-rpath'] = True
    tspec['has-elf-tls'] = True
    tspec['position-independent-executables'] = True

    # write out the target spec json file
    with open(wd + sys + '.json', 'w') as f:
        json.dump(tspec, f)


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
    import os
    import subprocess

    rust_base_sys = rust_base_triple(d, thing)
    arch = arch_for(d, thing)
    sys = sys_for(d, thing)
    prefix = prefix_for(d, thing)
    llvm_target = d.getVarFlag('LLVM_TARGET', arch, True)
    ldflags = d.getVar('LDFLAGS', True) + d.getVar('HOST_CC_ARCH', True) + d.getVar('TOOLCHAIN_OPTIONS', True)

    b = os.path.join(d.getVar('S', True), 'mk', 'cfg')
    o = open(os.path.join(b, sys_for(d, thing) + '.mk'), 'w')
    i = open(os.path.join(b, rust_base_sys + '.mk'), 'r')

    r = subprocess.call(['sed',
        # CFLAGS, LDFLAGS, CXXFLAGS, CPPFLAGS are used by rust's build for a
        # wide range of targets (not just HOST). Yocto's settings for them will
        # be inappropriate, avoid having random targets try to use them, we'll
        # add as needed.
        '-e', 's/$(CFLAGS)//',
        '-e', 's/$(CXXFLAGS)//',
        '-e', 's/$(CPPFLAGS)//',
        '-e', 's/$(LDFLAGS)//',

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
    # Note: this isn't how this variable is supposed to be used, but for
    # non-msvc platforms nothing else touches it.
    # These are the only extra flags passed to the rustllvm (c++ code) build.
    # These are only used for host (even though we emit them for all targets)
    # Without this, there are link failures due to GLIBC_CXX11_ABI issues in
    # certain setups.
    o.write("EXTRA_RUSTLLVM_CXXFLAGS_{} := {}\n".format(sys, cxxflags_for(d, thing)))
    o.close()
    i.close()

python do_rust_arch_fixup () {
    for thing in ['BUILD', 'HOST', 'TARGET']:
        bb.debug(1, "rust_gen_mk_cfg for " + thing)
        rust_gen_mk_cfg(d, thing)
}
addtask rust_arch_fixup before do_configure after do_patch
do_rust_arch_fixup[dirs] += "${S}/mk/cfg"

# prevent the rust-installer scripts from calling ldconfig
export CFG_DISABLE_LDCONFIG="notempty"

# rust's configure doesn't recognize --disable-static, so remove it.
DISABLE_STATIC = ""

do_configure () {
    # FIXME: target_prefix vs prefix, see cross.bbclass

    # - rpath is required otherwise rustc fails to resolve symbols
    # - submodule management is done by bitbake's fetching
    ${S}/configure                          \
        "--enable-rpath"                    \
        "--disable-docs"                    \
        "--disable-manage-submodules"       \
        "--disable-debug"                   \
        "--enable-optimize"                 \
        "--enable-optimize-cxx"             \
        "--disable-llvm-version-check"      \
        "--llvm-root=${STAGING_DIR_NATIVE}/${prefix_native}" \
        "--enable-optimize-tests"           \
        "--release-channel=stable"          \
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
        "--enable-local-rust"               \
        "--local-rust-root=${WORKDIR}/${RUST_SNAPSHOT}/rustc" \
        ${EXTRA_OECONF}
}

rust_runmake () {
    echo "COMPILE ${PN}" "$@"

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

    # Install our custom target.json files
    local td="${D}${libdir}/rustlib/"
    install -d "$td"
    for tgt in "${WORKDIR}/targets/"* ; do
        install -m 0644 "$tgt" "$td"
    done

    # Remove any files directly installed into libdir to avoid
    # conflicts between cross and native
    rm -f ${D}${libdir}/lib*.so

    # cleanup after rust-installer since we don't need these bits
    rm ${D}/${libdir}/rustlib/install.log
    rm ${D}/${libdir}/rustlib/rust-installer-version
    rm ${D}/${libdir}/rustlib/uninstall.sh
    rm ${D}/${libdir}/rustlib/components
}

do_install () {
    rust_do_install
}
# ex: sts=4 et sw=4 ts=8
