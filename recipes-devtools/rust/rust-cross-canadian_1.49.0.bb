require rust-cross-canadian.inc
require rust-source-${PV}.inc
require rust-snapshot-${PV}.inc

FILESEXTRAPATHS_prepend := "${THISDIR}/rust:"

SRC_URI += "\
    file://0001-rustc_target-Fix-dash-vs-underscore-mismatches-in-op.patch \
    "
