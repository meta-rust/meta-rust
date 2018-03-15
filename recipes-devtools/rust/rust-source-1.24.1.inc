# Specifics for Rust 1.24.1

SRC_URI += " \
	https://static.rust-lang.org/dist/rustc-${PV}-src.tar.gz;name=rust \
	file://rust-${PV}/fix-crate-ver-check.patch;patchdir=${WORKDIR}/rustc-${PV}-src \
"

SRC_URI[md5sum] = "50639bf359e658fcd713787d5898628d"
SRC_URI[sha256sum] = "3ea53d45e8d2e9a41afb3340cf54b9745f845b552d802d607707cf04450761ef"
SRC_URI[rust.md5sum] = "50639bf359e658fcd713787d5898628d"
SRC_URI[rust.sha256sum] = "3ea53d45e8d2e9a41afb3340cf54b9745f845b552d802d607707cf04450761ef"


# later versions of rust change the directory that they unextract to
RUSTSRC = "${WORKDIR}/rustc-${PV}-src"
# set this as our default
S = "${RUSTSRC}"

LIC_FILES_CHKSUM = "file://COPYRIGHT;md5=c709a09d1b062d9a908e3631c1e1cdf5"
