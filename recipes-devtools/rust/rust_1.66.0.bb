require rust-target.inc
require rust-source-${PV}.inc
require rust-snapshot-${PV}.inc

# The license file got updated for Rust 1.66.0+
LIC_FILES_CHKSUM = "file://COPYRIGHT;md5=92289ed52a60b63ab715612ad2915603"

INSANE_SKIP:${PN}:class-native = "already-stripped"

do_compile () {
    rust_runx build --stage 2
}

rust_do_install() {
    rust_runx install
}

python () {
    pn = d.getVar('PN')

    if not pn.endswith("-native"):
        raise bb.parse.SkipRecipe("Rust recipe doesn't work for target builds at this time. Fixes welcome.")
}

