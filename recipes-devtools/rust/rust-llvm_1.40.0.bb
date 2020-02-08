require rust-source-${PV}.inc
require rust-llvm.inc

LIC_FILES_CHKSUM = "file://LICENSE.TXT;md5=8a15a0759ef07f2682d2ba4b893c9afe"

do_install_prepend () {
	# the install does a sed on this without installing the file
	# we don't need it for anything
	mkdir -p "${D}/usr/share/llvm/cmake"
	touch "${D}/usr/share/llvm/cmake/LLVMExports-noconfig.cmake"
}

do_install_append () {
	# we don't need any of this stuff to build Rust
	rm -rf "${D}/usr/lib/cmake"
}
