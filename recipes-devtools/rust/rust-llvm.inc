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

EXTRA_OECMAKE_append_class-target = "\
  -DCROSS_TOOLCHAIN_FLAGS_NATIVE='-DCMAKE_TOOLCHAIN_FILE=${WORKDIR}/native_toolchain.cmake' \
"

do_generate_native_toolchain_file() {
        cat > ${WORKDIR}/native_toolchain.cmake <<EOF
set( CMAKE_SYSTEM_NAME `echo ${BUILD_OS} | sed -e 's/^./\u&/' -e 's/^\(Linux\).*/\1/'` )
set( CMAKE_SYSTEM_PROCESSOR ${BUILD_ARCH} )
set( CMAKE_C_COMPILER ${BUILD_CC} )
set( CMAKE_CXX_COMPILER ${BUILD_CXX} )
set( CMAKE_ASM_COMPILER ${BUILD_AS} )
set( CMAKE_AR ${BUILD_AR} CACHE FILEPATH "Archiver" )
set( CMAKE_C_FLAGS "${BUILD_CC_ARCH} ${BUILD_CFLAGS}" CACHE STRING "CFLAGS" )
set( CMAKE_CXX_FLAGS "${BUILD_CC_ARCH} ${BUILD_CXXFLAGS}" CACHE STRING "CXXFLAGS" )
set( CMAKE_ASM_FLAGS "${BUILD_CC_ARCH} ${BUILD_CFLAGS}" CACHE STRING "ASM FLAGS" )
set( CMAKE_C_FLAGS_RELEASE "${SELECTED_OPTIMIZATION} ${BUILD_CFLAGS} -DNDEBUG" CACHE STRING "CFLAGS for release" )
set( CMAKE_CXX_FLAGS_RELEASE "${SELECTED_OPTIMIZATION} ${BUILD_CXXFLAGS} -DNDEBUG" CACHE STRING "CXXFLAGS for release" )
set( CMAKE_ASM_FLAGS_RELEASE "${SELECTED_OPTIMIZATION} ${BUILD_CFLAGS} -DNDEBUG" CACHE STRING "ASM FLAGS for release" )
set( CMAKE_C_LINK_FLAGS "${BUILD_CC_ARCH} ${BUILD_CPPFLAGS} ${BUILD_LDFLAGS}" CACHE STRING "LDFLAGS" )
set( CMAKE_CXX_LINK_FLAGS "${BUILD_CC_ARCH} ${BUILD_CXXFLAGS} ${BUILD_LDFLAGS}" CACHE STRING "LDFLAGS" )

# only search in the paths provided so cmake doesnt pick
# up libraries and tools from the native build machine
set( CMAKE_FIND_ROOT_PATH ${STAGING_DIR_HOST} ${STAGING_DIR_NATIVE} ${CROSS_DIR} ${OECMAKE_PERLNATIVE_DIR} ${OECMAKE_EXTRA_ROOT_PATH} ${EXTERNAL_TOOLCHAIN})
set( CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY )
set( CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY )
set( CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY )

# Use native cmake modules
set( CMAKE_MODULE_PATH ${STAGING_DATADIR}/cmake/Modules/ )

# add for non /usr/lib libdir, e.g. /usr/lib64
set( CMAKE_LIBRARY_PATH ${libdir} ${base_libdir})

EOF
}

addtask generate_native_toolchain_file after do_patch before do_configure

do_configure_prepend_class-native() {
    # Use host paths for native tools
    sed -i -e '/CMAKE_FIND_ROOT_PATH_MODE/d' ${WORKDIR}/toolchain.cmake
}

do_compile_prepend_class-target() {
    # Fix paths in llvm-config
    sed -i "s|sys::path::parent_path(CurrentPath))\.str()|sys::path::parent_path(sys::path::parent_path(CurrentPath))).str()|g" ${S}/tools/llvm-config/llvm-config.cpp

    # Fix the hardcoded libdir in llvm-config
    sed -i 's:/lib\>:/${baselib}:g' ${S}/tools/llvm-config/llvm-config.cpp
}

do_compile() {
    oe_runmake
}

do_install_append_class-target() {
    # Disable checks on the native tools, since these should came from the native recipe
    sed -i -e 's/\(.*APPEND.*_IMPORT_CHECK_FILES_FOR_.*{_IMPORT_PREFIX}\/bin\/.*\)/#\1/' ${D}/usr/share/llvm/cmake/LLVMExports-noconfig.cmake
}

SYSROOT_PREPROCESS_FUNCS_append_class-target = " llvm_sysroot_preprocess"
SYSROOT_PREPROCESS_FUNCS_append_class-native = " llvm_native_sysroot_preprocess"

llvm_sysroot_preprocess() {
    install -d ${SYSROOT_DESTDIR}${bindir}
    cp ${B}/NATIVE/bin/llvm-config ${SYSROOT_DESTDIR}/${bindir} || bbfatal "missing llvm-config"
    cp ${B}/NATIVE/bin/llvm-tblgen ${SYSROOT_DESTDIR}/${bindir} || bbfatal "missing llvm-tblgen"
}

llvm_native_sysroot_preprocess() {
    sysroot_stage_dir ${D}${STAGING_DIR_NATIVE}/usr/libexec ${SYSROOT_DESTDIR}${bindir}
}

PACKAGES =+ "${PN}-bugpointpasses ${PN}-llvmhello ${PN}-liblto"

# Add the extra locations to avoid the complaints about unpackaged files
FILES_${PN} += "${libdir}/libLLVM*.so"
FILES_${PN}-dev += "${datadir}/llvm"
FILES_${PN}-bugpointpasses = "${libdir}/BugpointPasses.so"
FILES_${PN}-llvmhello = "${libdir}/LLVMHello.so"
FILES_${PN}-liblto = "${libdir}/libLTO.so"

BBCLASSEXTEND = "native"
