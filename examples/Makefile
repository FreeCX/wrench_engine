OS=$(shell uname -s)
ifeq ($(OS),Linux)
	LIB=../lib/libwrench.so
	PROG=window
else
	LIB=libwrench.dll
	PROG=window.exe
endif

all:
	$(CC) -L . $(LIB) window.c -o $(PROG)
clean:
	$(RM) $(PROG)