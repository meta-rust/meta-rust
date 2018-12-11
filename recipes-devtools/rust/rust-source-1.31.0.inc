# Specifics for Rust 1.31.0

SRC_URI += "https://static.rust-lang.org/dist/rustc-${PV}-src.tar.gz;name=rust"

SRC_URI[md5sum] = "f360954192dd6ce924a77e4f41abf05b"
SRC_URI[sha256sum] = "9ad54dc0baf1db5fc6a79d54e71c439c82aff85cd96778978456f2958211ef06"
SRC_URI[rust.md5sum] = "f360954192dd6ce924a77e4f41abf05b"
SRC_URI[rust.sha256sum] = "9ad54dc0baf1db5fc6a79d54e71c439c82aff85cd96778978456f2958211ef06"

# later versions of rust change the directory that they unextract to
RUSTSRC = "${WORKDIR}/rustc-${PV}-src"
# set this as our default
S = "${RUSTSRC}"

LIC_FILES_CHKSUM = "file://COPYRIGHT;md5=66ddc8ecd998476b7cd5732e8c3a6c1d"
