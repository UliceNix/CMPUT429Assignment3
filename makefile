CC=arm-gem5-linux-gnueabi-gcc
CFLAGS=-static -O1
all: way line cap

way: way.c timer.c timer.h
	$(CC) $(CFLAGS) way.c timer.c -o way
line: line.c timer.c timer.h
	$(CC) $(CFLAGS) line.c timer.c -o line
cap: cap.c timer.c timer.h
	$(CC) $(CFLAGS) cap.c timer.c -o cap
clean:
	rm -f way line cap
