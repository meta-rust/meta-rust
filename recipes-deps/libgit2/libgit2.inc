SUMMARY = "the Git linkable library"
HOMEPAGE = "http://libgit2.github.com/"
LICENSE = "GPL-2.0-with-linking-exception"

SRC_URI = "https://github.com/libgit2/libgit2/archive/v${PV}.tar.gz"

LIC_FILES_CHKSUM = "\
	file://COPYING;md5=29c24df0df4c2bab5efb8d5a33a73202 \
"

DEPENDS = "zlib"

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

BBCLASSEXTEND = "native"
