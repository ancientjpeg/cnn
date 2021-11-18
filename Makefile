CC = clang
CFLAGS = -std=c17 
TARGET = build/main


CSRCS = $(wildcard src/core/*.c)
OBJ = $(CSRCS:.c=.o)
LIB = /usr/local/lib
LIBFLAGS = $(LIB)/libimago.a -lpng -ljpeg

OBJCSRC = $(wildcard *.m)
MOBJ = $(OBJCSRC:.m=.o)
OBJCFLAGS =  -framework Foundation -framework Metal -framework CoreGraphics
DYLIBFLAGS = -dynamiclib
LINKFLAG = -L. -ltest
METALDYLIB = build/libtest.dylib

.PHONY: all
all: $(OBJ) libtest.dylib
	$(CC) -o $(TARGET) $(LIBFLAGS) $(LINKFLAGS) $(OBJ) $(METALDYLIB)
libtest.dylib: $(MOBJ)
	$(CC) $(OBJCFLAGS) $(DYLIBFLAGS) $(MOBJ) -o $(METALDYLIB)
.PHONY: clean
clean:
	rm $(OBJ)
