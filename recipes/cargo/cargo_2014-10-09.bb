SRCREV = "2d101e2e3809da5dc6c79c27ad962d7945cddfb5"

do_patch_prepend () {
	# Work around a bug in openssl-static-sys
	mkdir -p "${prefix}/lib"
	ln -sf "${base_prefix}/lib/libcrypto.a" "${prefix}/lib/"
}
require cargo.inc
