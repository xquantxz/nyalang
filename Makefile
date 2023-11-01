CFLAGS := -g -DDEBUG_AST
export CFLAGS

PHONY := all
all: analysis

PHONY += analysis
analysis:
	$(MAKE) -C analysis

PHONY += clean
clean:
	$(MAKE) -C analysis clean

.PHONY: $(PHONY)

