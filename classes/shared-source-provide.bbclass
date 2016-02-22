# In order to share the same source between multiple packages (.bb files), we
# unpack and patch the X source here into a shared dir.
#
# Take a look at gcc-source.inc for the general structure of this

# We require that "SOURCE_NAME" be set

# nopackages.bbclass {
deltask do_package
deltask do_package_write_rpm
deltask do_package_write_ipk
deltask do_package_write_deb
deltask do_package_qa
deltask do_packagedata
#}

deltask do_configure
deltask do_compile
deltask do_install
deltask do_populate_sysroot
deltask do_populate_lic
deltask do_rm_work


# override to get rid of '-native' or other misc
# XXX: consider ${PR}
PN = "${SOURCE_NAME}-source-${PV}"
WORKDIR = "${TMPDIR}/work-shared/${SOURCE_NAME}-${PV}-${PR}"
SSTATE_SWSPEC = "sstate:${SOURCE_NAME}::${PV}:${PR}::${SSTATE_VERSION}:"

STAMP = "${STAMPS_DIR}/work-shared/${SOURCE_NAME}-${PV}-${PR}"
STAMPCLEAN = "${STAMPS_DIR}/work-shared/${SOURCE_NAME}-${PV}-*"

INHIBIT_DEFAULT_DEPS = "1"
DEPENDS = ""
PACKAGES = ""

EXCLUDE_FROM_WORLD = "1"
