DEST = /usr/local/bin

myqrencode: myqrencode.c
	gcc -o myqrencode myqrencode.c qrcodegen.c

install: myqrencode
	install -s myqrencode $(DEST)