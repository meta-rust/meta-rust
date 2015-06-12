SUMMARY = "Rust runtime libaries"
HOMEPAGE = "http://www.rust-lang.org"
SECTION = "devel"
LICENSE = "MIT | Apache-2.0"

inherit rust-bin

DEPENDS += "virtual/${TARGET_PREFIX}rust"
RUSTLIB_DEP = ""

do_install () {
	mkdir -p ${D}/${rustlib}
	cp ${STAGING_DIR_NATIVE}/${rustlib}/*.so ${D}/${rustlib}
}

# This has no license file
python do_qa_configure() {
        return True
}

FILES_${PN} += "${rustlib}/*.so"
FILES_${PN}-dbg += "${rustlib}/.debug"
