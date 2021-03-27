require recipes-devtools/rust/rust-source-${PV}.inc
require recipes-devtools/rust/rust-snapshot-${PV}.inc
require cargo.inc

SRC_URI += "file://riscv-march.patch;patchdir=../../.."
SRC_URI += "file://rv64gc.patch;patchdir=../../.."
