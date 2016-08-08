# gcc's shared source code disables fetch (via the commented code below). We
# can't do that because rust.bb currently fetches a rustc-snapshot archive itself.
#do_fetch() {
#	:
#}
#do_fetch[noexec] = "1"

# gcc does `deltask` do_unpack. We avoid this so that the depends work sanely
# (things that need source code can still be ordered after do_unpack).
# As a side effect, we can also unpack things that aren't shared.
# Note: just setting this normally doesn't work. Use of python() is required.
python () {
	d.setVarFlag('do_unpack', 'cleandirs', '')
}
# Avoid disabling do_patch for the same reason.
#deltask do_patch

SRC_URI = ""

S = "${TMPDIR}/work-shared/${SOURCE_NAME}-${PV}-${PR}"

do_unpack[depends] += "${SOURCE_NAME}-source-${PV}:do_patch"
do_populate_lic[depends] += "${SOURCE_NAME}-source-${PV}:do_unpack"
