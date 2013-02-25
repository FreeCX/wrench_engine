ENGINE=../engine
SOURCES=$(ENGINE)/error.c $(ENGINE)/input.c $(ENGINE)/kernel.c $(ENGINE)/memory.c
LDFLAGS=
OS=$(shell uname -s)
ifeq ($(OS),Linux)
	LIB=libwrench.so
	CFLAGS=--def wrench.def -s -O3 -fPIC -shared -W -Wall -g \
		-lGL -lGLU -lX11 -lXxf86vm 
	SOURCES+=$(ENGINE)/linux.c
else
	LIB=libwrench.dll
	CFLAGS=-O3 -shared -Wl,-add-stdcall-alias -lopengl32 -lglu32 -lwinmm -lgdi32 wrench.def
	SOURCES+=$(ENGINE)/windows.c
endif

OBJS := $(patsubst %.c, %.o, $(SOURCES))
DEPS := $(patsubst %.o, %.d, $(OBJS))

$(LIB): $(OBJS) $(DEPS)
	$(CC) $(OBJS) -o $@ $(CFLAGS)
	strip -s $(LIB)
	chmod -x $(LIB)
 
%.o: %.c %.d
	$(CC) $(LDFLAGS) -c $< -o $@
 
%.d: %.c
	@set -e; $(CC) -M $< | \
		sed -e 's%\($*\)\.o[ :]*%\1.o $@ : %g' > $@; \
		[ -s $@ ] || rm -f $@
	@echo create $@
	
clean:
	rm -f $(OUT) $(OBJS) $(DEPS)
	rm -f *~
 
-include $(DEPS)