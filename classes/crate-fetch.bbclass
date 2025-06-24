#
# crate-fetch class
#
# Registers 'crate' method for Bitbake fetch2.
#
# Adds support for following format in recipe SRC_URI:
# crate://<packagename>/<version>
#

python () {
        import sys
        layerdir = d.getVar("RUSTLAYER")
        sys.path.insert(0, layerdir + "/lib")
        import crate
        bb.fetch2.methods.append( crate.Crate() )
}
