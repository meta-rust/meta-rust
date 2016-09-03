export rustlibdir = "${libdir}/rust"
FILES_${PN} += "${rustlibdir}/*.so"
FILES_${PN}-dev += "${rustlibdir}/*.rlib"
FILES_${PN}-dbg += "${rustlibdir}/.debug"

RUSTLIB = "-L ${STAGING_LIBDIR}/rust"
RUSTFLAGS += "-C rpath -C crate_hash=${BB_TASKHASH} ${RUSTLIB}"
RUSTLIB_DEP ?= "libstd-rs"
