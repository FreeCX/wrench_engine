LIB=libwrench.so
OUT=libwrench-`uname -m`.so
ENGINE=../engine
CFLAGS=--def wrench.def -O3 -fPIC -shared -W -Wall -g -lm -lGL -lGLU -lX11 -lXxf86vm 
SOURCES=$(ENGINE)/error.c $(ENGINE)/input.c $(ENGINE)/kernel.c $(ENGINE)/linux.c $(ENGINE)/memory.c

OBJS := $(patsubst %.c, %.o, $(SOURCES))
DEPS := $(patsubst %.o, %.d, $(OBJS))

$(LIB): $(OBJS) $(DEPS)
	$(CC) $(OBJS) -o $@ $(CFLAGS)
	chmod -x $(LIB)
	strip -s $(LIB)
	mv $(LIB) $(OUT)
 
%.o: %.c %.d
	$(CC) -c $< -o $@
 
%.d: %.c
	@set -e; $(CC) -M $< | \
		sed -e 's%\($*\)\.o[ :]*%\1.o $@ : %g' > $@; \
		[ -s $@ ] || rm -f $@
	@echo create $@
	
clean:
	rm -f $(OUT) $(OBJS) $(DEPS)
	rm -f *~
 
-include $(DEPS)