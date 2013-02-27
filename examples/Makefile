CFLAGS=-lm
OS=$(shell uname -s)
ifeq ($(OS),Linux)
	LIB=../lib/libwrench.so
	PROG=window
	CFLAGS+=-lGL
else
	LIB=libwrench.dll
	PROG=window.exe
	CFLAGS+=-lopengl32
endif

all:
	$(CC) $(CFLAGS) -L . $(LIB) window.c -o $(PROG)
clean:
	$(RM) $(PROG)