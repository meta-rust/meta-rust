SRC_URI += "https://static.rust-lang.org/dist/rustc-${PV}-src.tar.xz;name=rust"

SRC_URI[rust.md5sum] = "ee76b165cd95ef420765bfb568adb450"
SRC_URI[rust.sha256sum] = "4b0dbb356070687a606034f71dc032b783bbf8b5d3f9fff39f2c1fbc4f171c29"

# later versions of rust change the directory that they unextract to
RUSTSRC = "${WORKDIR}/rustc-${PV}-src"
# set this as our default
S = "${RUSTSRC}"

LLVM_LICENSE = "Apache-2.0-with-LLVM-exception"
LLVM_LIC_FILES_CHKSUM = "file://LICENSE.TXT;md5=8a15a0759ef07f2682d2ba4b893c9afe"

LIC_FILES_CHKSUM ?= "file://COPYRIGHT;md5=93a95682d51b4cb0a633a97046940ef0"
