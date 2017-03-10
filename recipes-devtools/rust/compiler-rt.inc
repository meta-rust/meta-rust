SUMMARY = "Rust compiler run-time"
HOMEPAGE = "http://www.rust-lang.org"
SECTION = "devel"
LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://src/compiler-rt/LICENSE.TXT;md5=bf24bca27049b52e9738451aa55771d4"

require rust.inc
ALLOW_EMPTY_${PN} = "1"

DEPENDS += "rust-llvm-native (=${PV})"
# dev and staticdev should NOT depend on the binary package
RDEPENDS_${PN}-dev = ""
INSANE_SKIP_${PN}-dev = "staticdev"

DISABLE_STATIC = ""
INHIBIT_DEFAULT_RUST_DEPS = "1"

do_compile () {
	oe_runmake ${TARGET_SYS}/rt/libcompiler-rt.a
}

do_install () {
	mkdir -p ${D}${libdir}
	cp ${TARGET_SYS}/rt/libcompiler-rt.a ${D}${libdir}/libcompiler-rt.a
}

FILES_${PN}-dev = ""
FILES_${PN}-staticdev = "${libdir}/*.a"
