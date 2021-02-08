require rust-target.inc
require rust-source-${PV}.inc
require rust-snapshot-${PV}.inc

SRC_URI += "\
    file://0001-rustc_target-Fix-dash-vs-underscore-mismatches-in-op.patch \
    "

do_compile () {
    rust_runx build --stage 2
}

rust_do_install() {
    rust_runx install
}
