SRC_URI += "https://static.rust-lang.org/dist/rustc-${PV}-src.tar.xz;name=rust"

SRC_URI[rust.md5sum] = "e8c9d1d39ceb0dd43ee0100d0f019da4"
SRC_URI[rust.sha256sum] = "38d6742e5c4c98a835de5d6e12a209e442fb3078a03b2c01bab6ea7afb25be6f"

# later versions of rust change the directory that they unextract to
RUSTSRC = "${WORKDIR}/rustc-${PV}-src"
# set this as our default
S = "${RUSTSRC}"

LIC_FILES_CHKSUM = "file://COPYRIGHT;md5=93a95682d51b4cb0a633a97046940ef0"
