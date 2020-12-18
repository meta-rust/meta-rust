SRC_URI += "https://static.rust-lang.org/dist/rustc-${PV}-src.tar.xz;name=rust"

SRC_URI[rust.sha256sum] = "ec2c81d2d34890486094a6407589be96161e4e301c238332d32c6dbae4f38ea2"

# later versions of rust change the directory that they unextract to
RUSTSRC = "${WORKDIR}/rustc-${PV}-src"
# set this as our default
S = "${RUSTSRC}"

LIC_FILES_CHKSUM = "file://COPYRIGHT;md5=93a95682d51b4cb0a633a97046940ef0"
