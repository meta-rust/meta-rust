SRC_URI += "https://static.rust-lang.org/dist/rustc-${PV}-src.tar.xz;name=rust"

SRC_URI[rust.sha256sum] = "d0899933840369f07394b211cb0b53a5cd4634907633f0bee541133c8b75e309"

# later versions of rust change the directory that they unextract to
RUSTSRC = "${WORKDIR}/rustc-${PV}-src"
# set this as our default
S = "${RUSTSRC}"

LLVM_LICENSE = "Apache-2.0-with-LLVM-exception"
LLVM_LIC_FILES_CHKSUM = "file://LICENSE.TXT;md5=8a15a0759ef07f2682d2ba4b893c9afe"

LIC_FILES_CHKSUM ?= "file://COPYRIGHT;md5=93a95682d51b4cb0a633a97046940ef0"
