CC=gcc
CFLAGS=-lpthread -Wall

all: Lab4.exe

Lab4.exe: Lab4.c
	$(CC) $(CFLAGS) -o Lab4.exe Lab4.c

.PHONY: clean
	del Lab4.exe