require rust-source-${PV}.inc
require libstd-rs.inc

LIC_FILES_CHKSUM = "file://../../COPYRIGHT;md5=c2cccf560306876da3913d79062a54b9"

# libstd moved from src/std to library/sysroot in 1.72+
S = "${RUSTSRC}/library/sysroot"
