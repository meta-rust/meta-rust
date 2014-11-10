
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

#BUILD_CFLAGS += "-fPIC"
#TARGET_CFLAGS += "-fPIC"

#| note: /usr/bin/ld: .../tmp/work/x86_64-linux/cargo-native/2014-11-07-r0/git/target/x86_64-unknown-linux-gnu/deps/libcurl-f3f9ef32955b72e6.rlib(r-curl-libcurl_la-openssl.o): undefined reference to symbol 'SSL_CTX_set_cipher_list'
#| /usr/lib/libssl.so.1.0.0: error adding symbols: DSO missing from command line
#DEPENDS_append = "openssl"
PACKAGECONFIG = "ipv6"
CFLAGS_append = " -fPIC"
