# Specifics for Rust 1.30.0

# SRC_URI += "https://static.rust-lang.org/dist/rustc-${PV}-src.tar.gz;name=rust"
SRC_URI += " \
        https://static.rust-lang.org/dist/rustc-${PV}-src.tar.gz;name=rust \
        file://skip-crate-build-id-check.patch;patchdir=${WORKDIR}/rustc-${PV}-src \
"




SRC_URI[md5sum] = "a4aec25d5a3987f62c3fb8c00178f3a2"
SRC_URI[sha256sum] = "cd0ba83fcca55b64c0c9f23130fe731dfc1882b73ae21bef96be8f2362c108ee"
SRC_URI[rust.md5sum] = "a4aec25d5a3987f62c3fb8c00178f3a2"
SRC_URI[rust.sha256sum] = "cd0ba83fcca55b64c0c9f23130fe731dfc1882b73ae21bef96be8f2362c108ee"

# later versions of rust change the directory that they unextract to
RUSTSRC = "${WORKDIR}/rustc-${PV}-src"
# set this as our default
S = "${RUSTSRC}"

LIC_FILES_CHKSUM = "file://COPYRIGHT;md5=66ddc8ecd998476b7cd5732e8c3a6c1d"
