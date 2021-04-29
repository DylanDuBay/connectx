CC = g++
CFLAGS = -Wall -g

BINS=main.o connectx

connectx: main.o 
	$(CC) $(CFLAGS) -o connectx main.o 

main.o: 
	$(CC) $(CFLAGS) -c src/main.cpp

clean:
	rm $(BINS)

