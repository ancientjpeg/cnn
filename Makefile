CC = clang
CFLAGS = -std=c17 -g
TARGET = main

CSRCS = $(wildcard src/*.c)
OBJ = $(CSRCS:.c=.o)

.PHONY: all
all: $(OBJ)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ)
	rm src/*.o

main: main.o