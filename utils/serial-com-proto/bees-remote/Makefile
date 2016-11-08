
target = bees-remote-test

cflags = -g

src = bees-serial.c \
	port.c \


ifdef READ
	src += test-read.c
else
	src += test-main.c
endif


inc = -I../../../apps/bees/src/

lib = -lncurses -lpthread

bees-remote-test: $(src)
	gcc $(src) $(inc) $(cflags) -o $(target) $(lib)

clean:
	rm $(target)
