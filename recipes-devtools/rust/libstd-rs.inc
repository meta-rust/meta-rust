SUMMARY = "Rust standard libaries"
HOMEPAGE = "http://www.rust-lang.org"
SECTION = "devel"
LICENSE = "MIT | Apache-2.0"

RUSTLIB_DEP = ""
inherit cargo

# Needed so cargo can find libbacktrace
RUSTFLAGS += "-L ${STAGING_LIBDIR} -C link-arg=-Wl,-soname,libstd.so"

S = "${RUSTSRC}/src/libstd"

do_compile_prepend () {
    export CARGO_TARGET_DIR="${B}"
    # For Rust 1.13.0 and newer
    export RUSTC_BOOTSTRAP="1"
}

do_install () {
    mkdir -p ${D}${rustlibdir}

    # With the incremental build support added in 1.24, the libstd deps directory also includes dependency
    # files that get installed. Those are really only needed to incrementally rebuild the libstd library
    # itself and don't need to be installed.
    rm ${B}/${TARGET_SYS}/release/deps/*.d
    cp ${B}/${TARGET_SYS}/release/deps/* ${D}${rustlibdir}
}
