require rust-target.inc
require rust-source-${PV}.inc
require rust-snapshot-${PV}.inc

# The default behaviour of x.py changed in 1.47+ so now we need to
# explicitly ask for the stage 2 compiler to be assembled.
do_compile () {
    rust_runx build --stage 2 src/rustc
}
