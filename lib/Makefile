ENGINE=../engine
SOURCES=$(ENGINE)/error.c $(ENGINE)/input.c $(ENGINE)/kernel.c $(ENGINE)/memory.c $(ENGINE)/unit/ui.c $(ENGINE)/unit/font.c
OS=$(shell uname -s)
ARCH=$(shell uname -m)

ifeq ($(OS),Linux)
	CFLAGS=-fPIC $(shell pkg-config fretype2 --cflags)
	LIB=libwrench-$(ARCH).so
	LFLAGS=-s -fPIC -shared -g -lGL -lGLU -lX11 -lXxf86vm $(shell pkg-config fretype2 --cflags --libs) --def wrench.def
	SOURCES+=$(ENGINE)/linux.c
else
	LIB=libwrench-$(ARCH).dll
	LFLAGS=-O3 -W -Wall -shared -Wl,-add-stdcall-alias -lopengl32 -lglu32 -lwinmm -lgdi32 \
		$(shell freetype-config --cflags --libs) wrench.def
	CFLAGS=$(shell freetype-config --cflags)
	SOURCES+=$(ENGINE)/windows.c
endif

OBJS := $(patsubst %.c, %.o, $(SOURCES))
DEPS := $(patsubst %.o, %.d, $(OBJS))

$(LIB): $(OBJS) $(DEPS)
	$(CC) $(OBJS) -o $@ $(LFLAGS)
	strip -s $(LIB)

%.o: %.c %.d
	$(CC) $(CFLAGS) -c $< -o $@

%.d: %.c
	@set -e; $(CC) -M $< | \
		sed -e 's%\($*\)\.o[ :]*%\1.o $@ : %g' > $@; \
		[ -s $@ ] || rm -f $@
	@echo create $@

clean:
	$(RM) $(LIB) $(OBJS) $(DEPS)
	$(RM) *~

-include $(DEPS)
