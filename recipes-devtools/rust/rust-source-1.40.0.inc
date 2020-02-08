SRC_URI += "https://static.rust-lang.org/dist/rustc-${PV}-src.tar.xz;name=rust"

SRC_URI[rust.md5sum] = "1725f67a1d92ab843a71fbbefef06db9"
SRC_URI[rust.sha256sum] = "6e2aa3a91697f4b225c6b394cbae6b97666f061dba491f666a5281698fe2aace"

# later versions of rust change the directory that they unextract to
RUSTSRC = "${WORKDIR}/rustc-${PV}-src"
# set this as our default
S = "${RUSTSRC}"

LIC_FILES_CHKSUM = "file://COPYRIGHT;md5=93a95682d51b4cb0a633a97046940ef0"
