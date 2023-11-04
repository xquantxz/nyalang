CFLAGS := -g -DDEBUG_AST
export CFLAGS

PHONY := all
all: compiler

PHONY += analysis
analysis:
	$(MAKE) -C $@

compiler: analysis main.c
	$(CC) main.c analysis/*.a -Iinclude $(CFLAGS) -o nyac

PHONY += clean
clean:
	$(MAKE) -C analysis clean
	$(MAKE) -C semantic clean
	rm -f *.o nyac

.PHONY: $(PHONY)

