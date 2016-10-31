inherit cargo

SRC_URI = "https://crates.io/api/v1/crates/rustfmt/0.4.0/download;downloadfilename=${P}.tar.gz"
SRC_URI[md5sum] = "2916b64ad7d6b6c9f33ea89f9b3083c4"
SRC_URI[sha256sum] = "add2143a74d9dde7ddbfdd325ac6f253656662fd3b6c22600e1fa4b52f9eab01"
LIC_FILES_CHKSUM="file://${COREBASE}/meta/COPYING.MIT;md5=3da9cfbcb788c80a0384361b4de20420"

SUMMARY = "Format Rust Code"
HOMEPAGE = "https://github.com/rust-lang-nursery/rustfmt"
LICENSE = "MIT | Apache-2.0"
