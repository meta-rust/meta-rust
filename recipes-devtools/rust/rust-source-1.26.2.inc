# Specifics for Rust 1.26.2

SRC_URI += " \
	https://static.rust-lang.org/dist/rustc-${PV}-src.tar.gz;name=rust \
	file://skip-crate-build-id-check.patch;patchdir=${WORKDIR}/rustc-${PV}-src \
"

SRC_URI[md5sum] = "581bc81b4695cff0d9b7c57a144d01cc"
SRC_URI[sha256sum] = "fb9ecf304488c9b56600ab20cfd1937482057f7e5db7899fddb86e0774548700"
SRC_URI[rust.md5sum] = "581bc81b4695cff0d9b7c57a144d01cc"
SRC_URI[rust.sha256sum] = "fb9ecf304488c9b56600ab20cfd1937482057f7e5db7899fddb86e0774548700"


# later versions of rust change the directory that they unextract to
RUSTSRC = "${WORKDIR}/rustc-${PV}-src"
# set this as our default
S = "${RUSTSRC}"

LIC_FILES_CHKSUM = "file://COPYRIGHT;md5=99c369ad81a36cd5b27f6c6968d01055"
