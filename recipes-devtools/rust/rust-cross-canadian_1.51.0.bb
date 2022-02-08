require recipes-devtools/rust/rust-cross-canadian.inc
require recipes-devtools/rust/rust-source-${PV}.inc
require recipes-devtools/rust/rust-snapshot-${PV}.inc

FILESEXTRAPATHS:prepend := "${THISDIR}/rust:"

