CC = clang
CFLAGS = -std=c17 -g
TARGET = main


CSRCS = $(wildcard src/*.c)
OBJ = $(CSRCS:.c=.o)
LIB = /usr/local/lib
LIBFLAGS = $(LIB)/libimago.a -lpng -ljpeg

.PHONY: all
all: $(OBJ)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ) $(LIBFLAGS) 


.PHONY: clean
clean:
	rm src/*.o
