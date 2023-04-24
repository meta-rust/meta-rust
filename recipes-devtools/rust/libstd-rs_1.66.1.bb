require rust-source-${PV}.inc
require libstd-rs.inc

LIC_FILES_CHKSUM = "file://../../COPYRIGHT;md5=92289ed52a60b63ab715612ad2915603"

# libstd moved from src/libstd to library/std in 1.47+
S = "${RUSTSRC}/library/std"
