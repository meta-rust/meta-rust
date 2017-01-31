require rust-llvm.inc
require rust-source-${PV}.inc

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
