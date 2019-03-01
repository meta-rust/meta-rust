require rust-source-${PV}.inc
require libstd-rs.inc

LIC_FILES_CHKSUM = "file://../../COPYRIGHT;md5=27e0aaa5e5cbd279af456711d3bdc066"

CARGO_FEATURES ?= "panic-unwind backtrace"

CARGO_VENDORING_DIRECTORY = "${RUSTSRC}/vendor"
