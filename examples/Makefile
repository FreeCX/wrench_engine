PROG=window
CFLAGS=-lm
OS=$(shell uname -s)
ifeq ($(OS),Linux)
	LIB=../lib/libwrench.so
	CFLAGS+=-lGL -lGLU
	EXT=
else
	LIB=libwrench.dll
	EXT=.exe
	CFLAGS+=-lopengl32 -lglu32
endif

all:
	$(CC) $(PROG).c $(CFLAGS) -L . $(LIB) -o $(PROG)$(EXT)
clean:
	$(RM) $(PROG)$(EXT)