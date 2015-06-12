inherit rust

RUSTLIB_DEP ?= " rustlib"
DEPENDS .= "${RUSTLIB_DEP}"
DEPENDS += "patchelf-native"

export rustlibdir = "${libdir}/rust"
FILES_${PN} += "${rustlibdir}/*.so"
FILES_${PN}-dev += "${rustlibdir}/*.rlib"
FILES_${PN}-dbg += "${rustlibdir}/.debug"

RUSTC_ARCHFLAGS += "-C opt-level=3 -L ${STAGING_DIR_HOST}/${rustlibdir}"
EXTRA_OEMAKE += 'RUSTC_ARCHFLAGS="${RUSTC_ARCHFLAGS}"'

rustlib="${libdir}/${TUNE_PKGARCH}${TARGET_VENDOR}-${TARGET_OS}/rustlib/${HOST_SYS}/lib"

do_rust_bin_fixups() {
    for f in `find ${PKGD} -name '*.so*'`; do
        echo "Strip rust note: $f"
        ${OBJCOPY} -R .note.rustc $f $f
    done

    for f in `find ${PKGD}`; do
        file "$f" | grep -q ELF || continue
        readelf -d "$f" | grep RPATH | grep -q rustlib || continue
        echo "Set rpath:" "$f"
        patchelf --set-rpath '$ORIGIN:'${rustlibdir}:${rustlib} "$f"
    done
}

PACKAGE_PREPROCESS_FUNCS += "do_rust_bin_fixups"
