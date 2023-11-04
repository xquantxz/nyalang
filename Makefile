CFLAGS := -g -DDEBUG_AST

ifeq ($(shell pkg-config --exists glib-2.0; echo $$?), 0)
	CFLAGS += $(shell pkg-config --cflags glib-2.0)
	LDFLAGS += $(shell pkg-config --libs glib-2.0)
else
	ERR := $(error GLib is not installed)
endif

export CFLAGS

PHONY := all
all: compiler

PHONY += analysis semantic
analysis semantic:
	$(MAKE) -C $@

compiler: analysis semantic main.c
	$(CC) main.c analysis/*.a semantic/*.a $(LDFLAGS) -Iinclude $(CFLAGS) -o nyac

PHONY += clean
clean:
	$(MAKE) -C analysis clean
	$(MAKE) -C semantic clean
	rm -f *.o nyac

.PHONY: $(PHONY)

