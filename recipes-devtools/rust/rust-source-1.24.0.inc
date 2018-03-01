# Specifics for Rust 1.24.0

SRC_URI += "\
	https://static.rust-lang.org/dist/rustc-${PV}-src.tar.gz;name=rust \
    "

SRC_URI[md5sum] = "068fc6566772c4ce165cc547151f514c"
SRC_URI[sha256sum] = "27b124fd0d94c082978ff81e45f7b7c37e91d64714587829bf828d64d76524ee"
SRC_URI[rust.md5sum] = "328b369e0cb5164b85c8067357a10291"
SRC_URI[rust.sha256sum] = "bb8276f6044e877e447f29f566e4bbf820fa51fea2f912d59b73233ffd95639f"


# later versions of rust change the directory that they unextract to
RUSTSRC = "${WORKDIR}/rustc-${PV}-src"
# set this as our default
S = "${RUSTSRC}"

LIC_FILES_CHKSUM = "file://COPYRIGHT;md5=c709a09d1b062d9a908e3631c1e1cdf5"
