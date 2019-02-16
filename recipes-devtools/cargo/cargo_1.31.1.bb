require recipes-devtools/rust/rust-source-${PV}.inc
require recipes-devtools/rust/rust-snapshot-${PV}.inc
require cargo.inc

# From 1.32.0, the vendor and target directory has moved.
CARGO_VENDORING_DIRECTORY = "${RUSTSRC}/src/vendor"
do_install () {
	install -d "${D}${bindir}"
	install -m 755 "${RUSTSRC}/src/target/${CARGO_TARGET_SUBDIR}/cargo" "${D}${bindir}"
}
