PROG=window
CFLAGS=-lm
OS=$(shell uname -s)
ARCH=$(shell uname -m)

ifeq ($(OS),Linux)
	LIB=../lib/libwrench-$(ARCH).so
	CFLAGS+=-lGL -lGLU  -I/usr/include/freetype2
	EXT=
else
	LIB=libwrench-$(ARCH).dll
	EXT=.exe
	CFLAGS+=-lopengl32 -lglu32
endif

all:
	$(CC) $(PROG).c $(CFLAGS) -L . $(LIB) -o $(PROG)$(EXT)
clean:
	$(RM) $(PROG)$(EXT)
