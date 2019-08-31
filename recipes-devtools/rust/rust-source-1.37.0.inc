SRC_URI += "https://static.rust-lang.org/dist/rustc-${PV}-src.tar.xz;name=rust"

SRC_URI[rust.md5sum] = "ee6300b1d7e5767115492915c4c0d8ef"
SRC_URI[rust.sha256sum] = "10abffac50a729cf74cef6dd03193a2f4647541bd19ee9281be9e5b12ca8cdfd"

# later versions of rust change the directory that they unextract to
RUSTSRC = "${WORKDIR}/rustc-${PV}-src"
# set this as our default
S = "${RUSTSRC}"

LIC_FILES_CHKSUM = "file://COPYRIGHT;md5=93a95682d51b4cb0a633a97046940ef0"
