SUMMARY = "the Git linkable library"
HOMEPAGE = "http://libgit2.github.com/"
LICENSE = "GPL-2.0-with-GCC-exception"

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

BBCLASSEXTEND = "native"
