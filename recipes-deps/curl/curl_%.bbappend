
## An excerpt from curl-sys's build script:
#export CFLAGS := $(CFLAGS) -fPIC -ffunction-sections -fdata-sections
#OPTS := $(OPTS) \
#        --enable-static=yes \
#        --enable-shared=no \
#	--disable-ldap --disable-ldaps --disable-ftp --disable-rtsp \
#	--disable-dict --disable-telnet --disable-tftp --disable-pop3 \
#	--disable-imap --disable-smtp --disable-gopher --disable-manual \
#	--enable-optimize --without-librtmp --without-libidn \
#        --prefix="$(OUT_DIR)"
## Due to how rust links, we need -fPIC. Without it,

#EXTRA_OECONF_append = " \
#	--with-zlib	\
#	--enable-static \
#	--enable-hidden-symbols \
#"

CFLAGS +=" -fPIC"

do_configure_prepend () {
	#export CFLAGS="$CFLAGS -fPIC"
}
