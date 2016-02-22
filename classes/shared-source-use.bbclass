S = "${TMPDIR}/work-shared/${SOURCE_NAME}-${PV}-${PR}"

do_unpack[depends] += "${SOURCE_NAME}-source-${PV}:do_patch"
