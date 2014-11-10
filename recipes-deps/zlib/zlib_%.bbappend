# cargo tries to build a shared object using several static objects, one of
# which includes the contents of zlib (zutil.o as 'libcurl-f3f9ef32955b72e6.rlib(r-z-zutil.o)')
CFLAGS_append = " -fPIC"
