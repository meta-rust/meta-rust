SUMMARY = "the Git linkable library"
HOMEPAGE = "http://libgit2.github.com/"
LICENSE = "GPL-2.0-with-linking-exception"

SRC_URI = "https://github.com/libgit2/libgit2/archive/v${PV}.tar.gz"

LIC_FILES_CHKSUM = "\
	file://COPYING;md5=29c24df0df4c2bab5efb8d5a33a73202 \
"

inherit cmake

# CLAR = tests, needs python-native
EXTRA_OECMAKE = "-DBUILD_CLAR=OFF"

BBCLASSEXTEND = "native"
