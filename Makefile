all: server1.o 
	gcc main.c -o server1.o -lpthread

server1.o: main.c
	gcc -c main.c -lpthread

clean:
	rm *.o
