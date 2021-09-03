require recipes-devtools/rust/rust-source-${PV}.inc
require recipes-devtools/rust/rust-snapshot-${PV}.inc

FILESEXTRAPATHS:prepend := "${THISDIR}/cargo-${PV}:"

require recipes-devtools/cargo/cargo-cross-canadian.inc
