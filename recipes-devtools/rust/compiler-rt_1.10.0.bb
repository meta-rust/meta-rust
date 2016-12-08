SUMMARY = "Rust compiler run-time"
HOMEPAGE = "http://www.rust-lang.org"
SECTION = "devel"
LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://LICENSE.TXT;md5=27b14ab4ce08d04c3a9a5f0ed7997362"

SRC_URI = "\
	https://static.rust-lang.org/dist/rustc-${PV}-src.tar.gz;name=rust \
    "

require rust-source-${PV}.inc

S = "${WORKDIR}/rustc-${PV}/src/compiler-rt"

do_compile () {
	oe_runmake -C ${S} \
		ProjSrcRoot="${S}" \
		ProjObjRoot="${B}" \
		CC="${CC}" \
		AR="${AR}" \
		RANLIB="${RANLIB}" \
		CFLAGS="${CFLAGS}" \
		TargetTriple=${HOST_SYS} \
		triple-builtins
}

do_install () {
	mkdir -p ${D}${libdir}
	cp triple/builtins/libcompiler_rt.a ${D}${libdir}/libcompiler-rt.a
}
