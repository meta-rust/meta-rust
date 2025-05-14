require rust-target.inc
require rust-source-${PV}.inc
require rust-snapshot-${PV}.inc

LIC_FILES_CHKSUM = "file://COPYRIGHT;md5=11a3899825f4376896e438c8c753f8dc"

INSANE_SKIP:${PN}:class-native = "already-stripped"

DEPENDS += "ninja-native"

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

