CC = clang
CFLAGS = -std=c17 
TARGET = build/main


CSRCS = $(wildcard src/core/*.c)
OBJ = $(CSRCS:.c=.o)
LIB = /usr/local/lib
LIBFLAGS = $(LIB)/libimago.a -lpng -ljpeg

OBJCSRC = $(wildcard src/metal/*.m)
MOBJ = $(OBJCSRC:.m=.o)
OBJCFLAGS =  -framework Foundation -framework Metal -framework CoreGraphics
DYLIBFLAGS = -dynamiclib
LINKFLAG = -L. -ltest
METALDYLIB = build/libcnnmetal.dylib

.PHONY: all
all: $(METALDYLIB) $(OBJ) 
	$(CC) -o $(TARGET) $(LIBFLAGS) $(LINKFLAGS) $(OBJ) $(METALDYLIB)
$(METALDYLIB): $(MOBJ)
	$(CC) $(OBJCFLAGS) $(DYLIBFLAGS) $(MOBJ) -o $(METALDYLIB)
%.o: %.c
	$(CC) -c -o $@ $<
%.o: %.m
	$(CC) -c -o $@ $<
.PHONY: clean
clean:
	rm $(OBJ) $(MOBJ)
