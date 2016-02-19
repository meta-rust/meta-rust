require rust-shared-source.inc

SUMMARY = "LLVM compiler framework (packaged with rust)"
LICENSE = "NCSA"

S .= "/src/llvm"

inherit autotools

EXTRA_OECONF += "--enable-targets=x86,x86_64,arm,aarch64,mips,powerpc"
EXTRA_OECONF += "--enable-optimized"
EXTRA_OECONF += "--disable-assertions"
EXTRA_OECONF += "--disable-docs"
EXTRA_OECONF += "--enable-bindings=none"
EXTRA_OECONF += "--disable-terminfo"
EXTRA_OECONF += "--disable-zlib"
EXTRA_OECONF += "--disable-libffi"

EXTRA_OECONF += "--enable-keep-symbols"

PACKAGES += "${PN}-data"

# Add the extra locations to avoid the complaints about unpackaged files
FILES_${PN}-data = "${datadir}"
FILES_${PN}-dev += "${libdir}"

do_install_append () {
	# Remove the debug info (>2 GB) as part of normal operation
	rm -rf ${D}${bindir}/.debug

	cd ${D}${bindir}
	ln -s *-llc llc
	for i in *-llvm-*; do
		link=$(echo $i | sed -e 's/.*-llvm-\(.*\)/\1/')
		ln -sf $i llvm-$link
	done
}

BBCLASSEXTEND = "native"
