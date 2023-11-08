all :
	gcc -o out/solwith.console.out m/m.c m/__lsifr.c \
  -DLINUX -D__NSOCKET__=1 -D__NSERIAL__=0  -D__NWEBSOCKET__=0  -D__NHTTPD__=0 -D__LINUX__=1 -D__TITLE__=1 \
  -I. -I./m -I./ua -I./coms -I./coms/__nio \
  -Xlinker --start-group \
  out/liblite.console.ua.x64.a coms/libio.x64.a coms/liblite.io.x64.a \
  -ldl -lm -lgcc_s -lpthread \
  -Xlinker --end-group
