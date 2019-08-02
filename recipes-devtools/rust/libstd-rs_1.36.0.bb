require rust-source-${PV}.inc
require libstd-rs.inc

LIC_FILES_CHKSUM = "file://../../COPYRIGHT;md5=93a95682d51b4cb0a633a97046940ef0"

CARGO_FEATURES ?= "panic-unwind backtrace"

CARGO_VENDORING_DIRECTORY = "${RUSTSRC}/vendor"
