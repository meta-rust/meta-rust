require rust-source-${PV}.inc
require libstd-rs.inc

SRC_URI += "file://riscv-march.patch;patchdir=../../"
SRC_URI += "file://rv64gc.patch;patchdir=../../"
# libstd moved from src/libstd to library/std in 1.47+
S = "${RUSTSRC}/library/std"
