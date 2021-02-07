require recipes-devtools/rust/rust-source-${PV}.inc
require recipes-devtools/rust/rust-snapshot-${PV}.inc
require cargo.inc

# This version has different LICENSE-APACHE and LICENSE-THIRD-PARTY

LIC_FILES_CHKSUM = " \
    file://LICENSE-MIT;md5=b377b220f43d747efdec40d69fcaa69d \
    file://LICENSE-APACHE;md5=1836efb2eb779966696f473ee8540542 \
    file://LICENSE-THIRD-PARTY;md5=892ea68b169e69cfe75097fc38a15b56 \
"
