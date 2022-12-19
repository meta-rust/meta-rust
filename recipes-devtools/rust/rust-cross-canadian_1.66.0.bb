require rust-cross-canadian.inc
require rust-source-${PV}.inc
require rust-snapshot-${PV}.inc

# The license file got updated for Rust 1.66.0+
LIC_FILES_CHKSUM = "file://COPYRIGHT;md5=92289ed52a60b63ab715612ad2915603"

FILESEXTRAPATHS:prepend := "${THISDIR}/rust:"
