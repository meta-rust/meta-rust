# Specifics for Rust 1.15.1

SRC_URI += "\
	https://static.rust-lang.org/dist/rustc-${PV}-src.tar.gz;name=rust \
    "
SRC_URI[rust.md5sum] = "5bbfff5ef8857a73d120616546a7fd29"
SRC_URI[rust.sha256sum] = "2e7daad418a830b45b977cd7ecf181b65f30f73df63ff36e124ea5fe5d1af327"

# later versions of rust change the directory that they unextract to
RUSTSRC = "${WORKDIR}/rustc-${PV}-src"
# set this as our default
S = "${RUSTSRC}"

LIC_FILES_CHKSUM = "file://COPYRIGHT;md5=43e1f1fb9c0ee3af66693d8c4fecafa8"
