require recipes-devtools/rust/rust-source-${PV}.inc
require recipes-devtools/rust/rust-snapshot-${PV}.inc
require cargo.inc

SRC_URI += "file://0001-Support-progress-on-other-than-tty-s.patch;striplevel=4"

LIC_FILES_CHKSUM += " \
    file://LICENSE-APACHE;md5=71b224ca933f0676e26d5c2e2271331c \
    file://LICENSE-THIRD-PARTY;md5=f257ad009884cb88a3a87d6920e7180a \
"
