# Specifics for Rust 1.27.1

SRC_URI += " \
	https://static.rust-lang.org/dist/rustc-${PV}-src.tar.gz;name=rust \
	file://skip-crate-build-id-check.patch;patchdir=${WORKDIR}/rustc-${PV}-src \
"

SRC_URI[md5sum] = "3d7f2a08caccb631b46084c31d2759c9"
SRC_URI[sha256sum] = "2133beb01ddc3aa09eebc769dd884533c6cfb08ce684f042497e097068d733d1"
SRC_URI[rust.md5sum] = "3d7f2a08caccb631b46084c31d2759c9"
SRC_URI[rust.sha256sum] = "2133beb01ddc3aa09eebc769dd884533c6cfb08ce684f042497e097068d733d1"

# later versions of rust change the directory that they unextract to
RUSTSRC = "${WORKDIR}/rustc-${PV}-src"
# set this as our default
S = "${RUSTSRC}"

LIC_FILES_CHKSUM = "file://COPYRIGHT;md5=99c369ad81a36cd5b27f6c6968d01055"
