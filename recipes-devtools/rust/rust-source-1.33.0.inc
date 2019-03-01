SRC_URI += "https://static.rust-lang.org/dist/rustc-${PV}-src.tar.gz;name=rust"

SRC_URI[rust.md5sum] = "54b688b5bc328ae72d8bfcf218969cea"
SRC_URI[rust.sha256sum] = "5a01a8d7e65126f6079042831385e77485fa5c014bf217e9f3e4aff36a485d94"

# later versions of rust change the directory that they unextract to
RUSTSRC = "${WORKDIR}/rustc-${PV}-src"
# set this as our default
S = "${RUSTSRC}"

LIC_FILES_CHKSUM = "file://COPYRIGHT;md5=27e0aaa5e5cbd279af456711d3bdc066"
