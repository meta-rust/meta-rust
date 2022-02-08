require recipes-devtools/rust/rust-target.inc
require recipes-devtools/rust/rust-source-${PV}.inc
require recipes-devtools/rust/rust-snapshot-${PV}.inc

SRC_URI += " \
             file://riscv-march.patch \
             file://rv64gc.patch \
           "

do_compile () {
    rust_runx build --stage 2
}

rust_do_install() {
    rust_runx install
}
