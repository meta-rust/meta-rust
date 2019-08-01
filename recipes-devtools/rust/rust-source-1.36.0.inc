SRC_URI += "https://static.rust-lang.org/dist/rustc-${PV}-src.tar.gz;name=rust"

SRC_URI[rust.md5sum] = "90804a5e0d7e4027c5373f4240c757ca"
SRC_URI[rust.sha256sum] = "04c4e4d7213d036d6aaed392841496d272146312c0290f728b7400fccd15bb1b"

# later versions of rust change the directory that they unextract to
RUSTSRC = "${WORKDIR}/rustc-${PV}-src"
# set this as our default
S = "${RUSTSRC}"

LIC_FILES_CHKSUM = "file://COPYRIGHT;md5=93a95682d51b4cb0a633a97046940ef0"
