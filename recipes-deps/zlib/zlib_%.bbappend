# cargo tries to build a shared object using several static objects, one of
# which includes the contenst of zlib (zutil.o)
do_configure_prepend () {
	export CFLAGS="${CFLAGS} -fPIC"
}
