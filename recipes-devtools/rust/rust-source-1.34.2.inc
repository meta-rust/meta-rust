SRC_URI += "https://static.rust-lang.org/dist/rustc-${PV}-src.tar.gz;name=rust"

SRC_URI[rust.md5sum] = "7c85e6a60dda740295f7e004a1fb15e1"
SRC_URI[rust.sha256sum] = "c69a4a85a1c464368597df8878cb9e1121aae93e215616d45ad7d23af3052f56"

# later versions of rust change the directory that they unextract to
RUSTSRC = "${WORKDIR}/rustc-${PV}-src"
# set this as our default
S = "${RUSTSRC}"

LIC_FILES_CHKSUM = "file://COPYRIGHT;md5=93a95682d51b4cb0a633a97046940ef0"
