SUMMARY = "LLVM compiler framework (packaged with rust)"
LICENSE = "NCSA"

SRC_URI += "file://0002-llvm-allow-env-override-of-exe-path.patch"

S = "${RUSTSRC}/src/llvm-project/llvm"

LIC_FILES_CHKSUM = "file://LICENSE.TXT;md5=4c0bc17c954e99fd547528d938832bfa"

inherit cmake pythonnative

DEPENDS += "ninja-native rust-llvm-native"

ARM_INSTRUCTION_SET_armv5 = "arm"
ARM_INSTRUCTION_SET_armv4t = "arm"

LLVM_RELEASE = "6.0"
LLVM_DIR = "llvm${LLVM_RELEASE}"

EXTRA_OECMAKE = " \
    -DCMAKE_BUILD_TYPE=Release \
    -DLLVM_TARGETS_TO_BUILD='X86;ARM;AArch64;PowerPC;Mips' \
    -DLLVM_BUILD_DOCS=OFF \
    -DLLVM_ENABLE_TERMINFO=OFF \
    -DLLVM_ENABLE_ZLIB=OFF \
    -DLLVM_ENABLE_LIBXML2=OFF \
    -DLLVM_ENABLE_FFI=OFF \
    -DLLVM_INSTALL_UTILS=ON \
    -DLLVM_BUILD_EXAMPLES=OFF \
    -DLLVM_INCLUDE_EXAMPLES=OFF \
    -DLLVM_BUILD_TESTS=OFF \
    -DLLVM_INCLUDE_TESTS=OFF \
    -DLLVM_TARGET_ARCH=${TARGET_ARCH} \
    -DCMAKE_INSTALL_PREFIX:PATH=${libdir}/llvm-rust \
"
EXTRA_OECMAKE_append_class-target = "\
    -DCMAKE_CROSSCOMPILING:BOOL=ON \
    -DLLVM_BUILD_TOOLS=OFF \
    -DLLVM_TABLEGEN=${STAGING_LIBDIR_NATIVE}/llvm-rust/bin/llvm-tblgen \
    -DLLVM_CONFIG_PATH=${STAGING_LIBDIR_NATIVE}/llvm-rust/bin/llvm-config \
"

# The debug symbols are huge here (>2GB) so suppress them since they
# provide almost no value. If you really need them then override this
INHIBIT_PACKAGE_DEBUG_SPLIT = "1"

do_install_append_class-target() {
    # Disable checks on the native tools, since these should came from the native recipe
    sed -i -e 's/\(.*APPEND.*_IMPORT_CHECK_FILES_FOR_.*{_IMPORT_PREFIX}\/bin\/.*\)/#\1/' ${D}/usr/share/llvm/cmake/LLVMExports-noconfig.cmake
}

PACKAGES =+ "${PN}-bugpointpasses ${PN}-llvmhello ${PN}-liblto"

# Add the extra locations to avoid the complaints about unpackaged files
FILES_${PN}-bugpointpasses = "${libdir}/llvm-rust/lib/BugpointPasses.so"
FILES_${PN}-llvmhello = "${libdir}/llvm-rust/lib/LLVMHello.so"
FILES_${PN}-liblto = "${libdir}/llvm-rust/lib/libLTO.so.*"
FILES_${PN}-staticdev =+ "${libdir}/llvm-rust/*/*.a"
FILES_${PN} += "${libdir}/libLLVM*.so.* ${libdir}/llvm-rust/lib/*.so.* ${libdir}/llvm-rust/bin"
FILES_${PN}-dev += "${datadir}/llvm ${libdir}/llvm-rust/lib/*.so ${libdir}/llvm-rust/include ${libdir}/llvm-rust/share ${libdir}/llvm-rust/lib/cmake"

BBCLASSEXTEND = "native"
