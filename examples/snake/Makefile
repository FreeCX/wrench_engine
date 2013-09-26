PROG=snake
CFLAGS=-lm
OS=$(shell uname -s)
ARCH=$(shell uname -m)

ifeq ($(OS),Linux)
	LIB=../../lib/libwrench-$(ARCH).so
	CFLAGS+=-lGL -lGLU `pkg-config freetype2 --cflags`
	EXT=
else
	LIB=libwrench-$(ARCH).dll
	EXT=.exe
	CFLAGS+=-lopengl32 -lglu32
endif

all:
	$(CC) snake.c game.c $(CFLAGS) -L . $(LIB) -o $(PROG)$(EXT)
clean:
	$(RM) $(PROG)$(EXT)
