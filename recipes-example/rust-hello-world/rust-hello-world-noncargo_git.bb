include rust-hello-world.inc

inherit rust-bin

do_compile () {
    oe_compile_rust_bin
}

do_install () {
    oe_compile_rust_bin
}
