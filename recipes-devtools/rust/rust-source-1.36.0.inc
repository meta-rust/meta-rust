SRC_URI += "https://static.rust-lang.org/dist/rustc-${PV}-src.tar.xz;name=rust"

SRC_URI[rust.md5sum] = "78ffc0b029aaed216b45c3fe24747d46"
SRC_URI[rust.sha256sum] = "f51645b9f787af4a5d94db17f6af39db0c55980ed24fe366cad55b57900f8f2d"

# later versions of rust change the directory that they unextract to
RUSTSRC = "${WORKDIR}/rustc-${PV}-src"
# set this as our default
S = "${RUSTSRC}"

LIC_FILES_CHKSUM = "file://COPYRIGHT;md5=93a95682d51b4cb0a633a97046940ef0"
