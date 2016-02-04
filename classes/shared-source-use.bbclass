S = "${TMPDIR}/work-shared/${SOURCE_NAME}-${PV}-${PR}"

do_configure[depends] += "${SOURCE_NAME}-source-${PV}:do_patch"
do_populate_lic[depends] += "${SOURCE_NAME}-source-${PV}:do_unpack"
