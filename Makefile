CC=gcc
CFLAGS=-O

myqrencode: myqrencode.c
	$(CC) $(CFLAGS) -o myqrencode myqrencode.c qrcodegen.c -lncurses