a: client.o server.o
	gcc client.o server.o
client.o: client.c 1.h
	gcc -c client.c
server.o: server.c 1.h
	gcc -c server.c

