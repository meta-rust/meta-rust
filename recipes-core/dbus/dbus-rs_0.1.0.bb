DESCRIPTION = "DBus binding for rust"
HOMEPAGE = "https://github.com/diwic/dbus-rs"
LICENSE = "Apache-2.0"
LIC_FILES_CHKSUM = "file://LICENSE;md5=d2794c0df5b907fdace235a619d80314"
DEPENDS = "libc-rs dbus"

inherit rust-bin

SRC_URI = "git://github.com/diwic/dbus-rs.git;protocol=https"
SRCREV = "d23c8b7fecd5a8e82131893250a5ac376799faff"

S = "${WORKDIR}/git"

do_compile () {
	oe_compile_rust_lib
}

do_install () {
	oe_install_rust_lib
}
