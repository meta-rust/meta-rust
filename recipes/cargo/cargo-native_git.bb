SUMMARY = "Cargo downloads your Rust project's dependencies and builds your project"
HOMEPAGE = "http://crates.io"
SECTION = "devel"
LICENSE = "MIT | Apache-2.0"

LIC_FILES_CHKSUM ="\
    file://LICENSE-MIT;md5=362255802eb5aa87810d12ddf3cfedb4 \
    file://LICENSE-APACHE;md5=1836efb2eb779966696f473ee8540542 \
    file://LICENSE-THIRD-PARTY;md5=afbb7ae0aa70c8e437a007314eae5f3b \
"

SRC_URI = " \
    https://static.rust-lang.org/cargo-dist/2015-04-02/cargo-nightly-x86_64-unknown-linux-gnu.tar.gz \
"

SRC_URI[md5sum] = "3d62194d02a9088cd8aae379e9498134"
SRC_URI[sha256sum] = "16b6338ba2942989693984ba4dbd057c2801e8805e6da8fa7b781b00e722d117"

S = "${WORKDIR}/cargo-nightly-x86_64-unknown-linux-gnu/"

inherit native 

do_install() {
    sh ${S}/install.sh --destdir=${STAGING_DIR_NATIVE} --prefix= 
}
