# Specifics for Rust 1.21.0

SRC_URI += "\
	https://static.rust-lang.org/dist/rustc-${PV}-src.tar.gz;name=rust \
    "
SRC_URI[rust.md5sum] = "bc494706b764276613064aad52922f53"
SRC_URI[rust.sha256sum] = "1707c142244b5bd909993559c6116c81987c1de21d6207c05d3ecbe5bba548fa"

# later versions of rust change the directory that they unextract to
RUSTSRC = "${WORKDIR}/rustc-${PV}-src"
# set this as our default
S = "${RUSTSRC}"

LIC_FILES_CHKSUM = "file://COPYRIGHT;md5=c709a09d1b062d9a908e3631c1e1cdf5"
