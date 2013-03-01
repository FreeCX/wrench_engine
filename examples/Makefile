CFLAGS=-lm
OS=$(shell uname -s)
ifeq ($(OS),Linux)
	LIB=../lib/libwrench.so
	PROG=window
	CFLAGS+=-lGL -lGLU
else
	LIB=libwrench.dll
	PROG=window.exe
	CFLAGS+=-lopengl32 -lglu32
endif

all:
	$(CC) window.c $(CFLAGS) -L . $(LIB) -o $(PROG)
clean:
	$(RM) $(PROG)