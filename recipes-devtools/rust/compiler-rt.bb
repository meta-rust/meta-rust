SUMMARY = "Rust compiler run-time"
HOMEPAGE = "http://www.rust-lang.org"
SECTION = "devel"
LICENSE = "MIT"

require rust-shared-source.inc
LIC_FILES_CHKSUM = "file://LICENSE.TXT;md5=27b14ab4ce08d04c3a9a5f0ed7997362"

S .= "/src/compiler-rt"
B = "${WORKDIR}/build"

# Pick up $CC from the environment
EXTRA_OEMAKE += "-e"

do_compile () {
	oe_runmake -C ${S} \
		ProjSrcRoot="${S}" \
		ProjObjRoot="${B}" \
		TargetTriple=${HOST_SYS} \
		triple-builtins
}

do_install () {
	mkdir -p ${D}${libdir}
	cp triple/builtins/libcompiler_rt.a ${D}${libdir}/libcompiler-rt.a
}
