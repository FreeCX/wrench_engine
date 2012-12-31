LIB="libwrench-`uname -m`.so"
ENGINE=../engine
CFLAGS=-O9 -fPIC -g -shared -W -Wall -g -lm -lGL -lGLU -lX11 -lXxf86vm -masm=intel 
SOURCE=$(ENGINE)/error.c $(ENGINE)/input.c $(ENGINE)/kernel.c $(ENGINE)/linux.c $(ENGINE)/memory.c

all:
	$(CC) $(SOURCE) $(CFLAGS) -o $(LIB)
	chmod -x $(LIB)
	strip -s $(LIB)
clean:
	$(RM) $(LIB) 
