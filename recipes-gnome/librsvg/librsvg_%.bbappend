FILESEXTRAPATHS:prepend := "${THISDIR}/${PN}:"

SRC_URI += "${@ "file://0002-allow-invalid-ref-casting-to-allow-building.patch" if bb.utils.vercmp_string_op(d.getVar('PV', True), "2.52.10", "==") else ""}"

TARGET_CC_ARCH += "${@ "${LDFLAGS}" if bb.utils.vercmp_string_op(d.getVar('PV', True), "2.52.10", "==") else ""}"
