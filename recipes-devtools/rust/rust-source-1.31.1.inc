# Specifics for Rust 1.31.1

SRC_URI += "https://static.rust-lang.org/dist/rustc-${PV}-src.tar.gz;name=rust"

SRC_URI[md5sum] = "f6ef68a5cf5c420943228750e33b691a"
SRC_URI[sha256sum] = "91d2fc22f08d986adab7a54eb3a6a9b99e490f677d2d092e5b9e4e069c23686a"
SRC_URI[rust.md5sum] = "f6ef68a5cf5c420943228750e33b691a"
SRC_URI[rust.sha256sum] = "91d2fc22f08d986adab7a54eb3a6a9b99e490f677d2d092e5b9e4e069c23686a"

# later versions of rust change the directory that they unextract to
RUSTSRC = "${WORKDIR}/rustc-${PV}-src"
# set this as our default
S = "${RUSTSRC}"

LIC_FILES_CHKSUM = "file://COPYRIGHT;md5=66ddc8ecd998476b7cd5732e8c3a6c1d"
