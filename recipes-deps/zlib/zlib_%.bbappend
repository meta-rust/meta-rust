# cargo tries to build a shared object using several static objects, one of
# which includes the contenst of zlib (zutil.o)
CFLAGS += " -fPIC"
