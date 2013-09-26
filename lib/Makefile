ENGINE=../engine
SOURCES=$(ENGINE)/error.c $(ENGINE)/input.c $(ENGINE)/kernel.c \
	$(ENGINE)/memory.c $(ENGINE)/unit/ui.c $(ENGINE)/unit/font.c
OS=$(shell uname -s)
ARCH=$(shell uname -m)
CFLAGS=`pkg-config freetype2 --libs` -O3 -W -Wall
LDFLAGS=`pkg-config freetype2 --cflags`

ifeq ($(OS),Linux)
	LDFLAGS+=-fPIC
	LIB=libwrench-$(ARCH).so
	CFLAGS+=--def wrench.def -s -fPIC -shared -g -lGL -lGLU \
		-lX11 -lXxf86vm
	SOURCES+=$(ENGINE)/linux.c
else
	LIB=libwrench-$(ARCH).dll
	CFLAGS+=-shared -Wl,-add-stdcall-alias -lopengl32 -lglu32 \
		-lwinmm -lgdi32 wrench.def
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
	@set -e; $(CC) -I/usr/include/freetype2 -M $< | \
		sed -e 's%\($*\)\.o[ :]*%\1.o $@ : %g' > $@; \
		[ -s $@ ] || rm -f $@
	@echo create $@

clean:
	$(RM) $(LIB) $(OBJS) $(DEPS)
	$(RM) *~

-include $(DEPS)
