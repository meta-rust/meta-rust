require rust-llvm.inc

LIC_FILES_CHKSUM = "file://LICENSE.TXT;md5=4c0bc17c954e99fd547528d938832bfa"

do_install_append () {
	cd "${B}"
	install -d "${D}${bindir}"
	install -m755 "Release/bin/FileCheck" "${D}${bindir}"
}
