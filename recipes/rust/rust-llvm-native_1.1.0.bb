SUMMARY = "LLVM compiler framework (packaged with rust)"
LICENSE = "NCSA"

LIC_FILES_CHKSUM = "file://LICENSE.TXT;md5=47e311aa9caedd1b3abf098bd7814d1d"

# 1.1.0
require rust-release.inc
SRC_URI[rust.md5sum] = "5f2f923f8d1c77a55721d1f0813a158a"
SRC_URI[rust.sha256sum] = "cb09f443b37ec1b81fe73c04eb413f9f656859cf7d00bc5088008cbc2a63fa8a"

S = "${WORKDIR}/rustc-${PV}/src/llvm"

inherit autotools
inherit native

EXTRA_OECONF += "--enable-targets=x86,x86_64,arm,aarch64,mips,powerpc"
EXTRA_OECONF += "--enable-optimized"
EXTRA_OECONF += "--disable-bindings"
EXTRA_OECONF += "--enable-keep-symbols"

do_install_append () {
	cd ${D}${bindir}
	ln -s *-llc llc
	for i in *-llvm-*; do
		link=$(echo $i | sed -e 's/.*-llvm-\(.*\)/\1/')
		ln -s $i llvm-$link
	done
}
