SUMMARY = "Rust runtime libaries"
HOMEPAGE = "http://www.rust-lang.org"
SECTION = "devel"
LICENSE = "MIT | Apache-2.0"

inherit rust-bin

DEPENDS += "virtual/${TARGET_PREFIX}rust"
RUSTLIB_DEP = ""

do_install () {
	for f in ${STAGING_DIR_NATIVE}/${rustlib_src}/*; do
		echo Installing $f
		install -D -m 755 $f ${D}/${rustlib}/$(basename $f)
	done
}

# This has no license file
python do_qa_configure() {
        return True
}

FILES_${PN} += "${rustlib}/*.so"
FILES_${PN}-dev += "${rustlib}/*.rlib"
FILES_${PN}-staticdev += "${rustlib}/*.a"
FILES_${PN}-dbg += "${rustlib}/.debug"
