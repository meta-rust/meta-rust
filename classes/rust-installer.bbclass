# Rust installer isn't very nice and drops a bunch of junk in our filesystem,
# clean it up after the install.

rust_installer_do_install () {
	rm ${D}/${libdir}/rustlib/install.log
	rm ${D}/${libdir}/rustlib/rust-installer-version
	rm ${D}/${libdir}/rustlib/uninstall.sh
	rm ${D}/${libdir}/rustlib/components
}

do_install_append () {
	rust_installer_do_install
}

EXPORT_FUNCTIONS rust_installer_do_install
