SUMMARY = "the Git linkable library"
HOMEPAGE = "http://libgit2.github.com/"
LICENSE = "GPL-2.0-with-linking-exception"

DEPENDS = "openssl zlib"

inherit cmake

# CLAR = tests, needs python-native
EXTRA_OECMAKE = "\
	-DTHREADSAFE=ON \
	-DBUILD_CLAR=OFF \
	-DSHA1_TYPE="builtin" \
	-DCMAKE_BUILD_TYPE=RelWithDebInfo \
	-DBUILD_SHARED_LIBS=OFF \
	-DBUILD_EXAMPLES=OFF \
"

CFLAGS_append .= " -fPIC"

# Prior to poky commit 60d504b431fa7cdc6ded141def7ae18edb1834e5,
# the cmake class did not define CMAKE_AR in the generated toolchain
# file.  This is needed to support building a static library.
# See https://github.com/jmesmon/meta-rust/issues/1
OECMAKE_AR ?= "${AR}"
cmake_do_generate_toolchain_file_append() {
    cat >> ${WORKDIR}/toolchain.cmake <<EOF
set( CMAKE_AR ${OECMAKE_AR} CACHE FILEPATH "Archiver" )
EOF
}

BBCLASSEXTEND = "native"
