CFLAGS += -I../include
OBJS := symtable.o collect.o ../type.o

__all: libnsem.a

libnsem.a: $(OBJS)
	ar rcs $@ $(OBJS)

clean:
	rm -rf *.o *.a

.PHONY: clean


