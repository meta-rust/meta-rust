SUMMARY = "Rust compiler run-time"
HOMEPAGE = "http://www.rust-lang.org"
SECTION = "devel"
LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://LICENSE.TXT;md5=27b14ab4ce08d04c3a9a5f0ed7997362"

SRC_URI = "\
	https://static.rust-lang.org/dist/rustc-${PV}-src.tar.gz;name=rust \
    "
SRC_URI[rust.md5sum] = "a48fef30353fc9daa70b484b690ce5db"
SRC_URI[rust.sha256sum] = "a4015aacf4f6d8a8239253c4da46e7abaa8584f8214d1828d2ff0a8f56176869"

S = "${WORKDIR}/rustc-${PV}/src/compiler-rt"

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
