require rust-source-${PV}.inc
require libstd-rs.inc

LIC_FILES_CHKSUM = "file://../../COPYRIGHT;md5=66ddc8ecd998476b7cd5732e8c3a6c1d"

CARGO_FEATURES ?= "panic-unwind backtrace"

CARGO_VENDORING_DIRECTORY = "${RUSTSRC}/vendor"
