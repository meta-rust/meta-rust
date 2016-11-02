SUMMARY = "LLVM compiler framework (packaged with rust)"
LICENSE = "NCSA"

SRC_URI = "\
	https://static.rust-lang.org/dist/rustc-${PV}-src.tar.gz;name=rust \
"

S = "${WORKDIR}/rustc-${PV}/src/llvm"

LIC_FILES_CHKSUM = "file://LICENSE.TXT;md5=4c0bc17c954e99fd547528d938832bfa"

inherit cmake pythonnative

EXTRA_OECMAKE = " \
    -DLLVM_TARGETS_TO_BUILD='X86;ARM;AArch64;PowerPC' \
    -DLLVM_ENABLE_ASSERTIONS=OFF \
    -DLLVM_BUILD_DOCS=OFF \
    -DLLVM_ENABLE_TERMINFO=OFF \
    -DLLVM_ENABLE_ZLIB=OFF \
    -DLLVM_ENABLE_FFI=OFF \
    -DLLVM_INSTALL_UTILS=ON \
    -DLLVM_BUILD_TOOLS=ON \
    -DLLVM_BUILD_EXAMPLES=OFF \
    -DLLVM_INCLUDE_EXAMPLES=OFF \
    -DLLVM_BUILD_TESTS=OFF \
    -DLLVM_INCLUDE_TESTS=OFF \
    -DLLVM_TARGET_ARCH=${TARGET_ARCH} \
"

# The debug symbols are huge here (>2GB) so suppress them since they
# provide almost no value. If you really need them then override this
INHIBIT_PACKAGE_DEBUG_SPLIT = "1"

PACKAGES += "${PN}-data"

# Add the extra locations to avoid the complaints about unpackaged files
FILES_${PN}-data = "${datadir}"
FILES_${PN}-dev += "${libdir}"

BBCLASSEXTEND = "native"
