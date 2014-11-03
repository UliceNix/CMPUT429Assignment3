# one needs to export /cshome/c429ss/arm-gem5-linux-gnueabi/bin to PATH
# in order to use this makefile
CC=arm-gem5-linux-gnueabi-gcc
CFLAGS=-static -O1
all: way.arm line.arm cap.arm

way.arm: way.c timer.c timer.h
	$(CC) $(CFLAGS) way.c timer.c -o way.arm
line.arm: line.c timer.c timer.h
	$(CC) $(CFLAGS) line.c timer.c -o line.arm
cap.arm: cap.c timer.c timer.h
	$(CC) $(CFLAGS) cap.c timer.c -o cap.arm
clean:
	rm -f way line cap
