YIELD_OBJECTS := $(patsubst %.s,%.o,$(wildcard yield_*.s))
OBJECTS += $(YIELD_OBJECTS) coro.o

%.o: %.s
	$(CC) $(CCFLAGS) -o $@ -c -x assembler-with-cpp $<

%.o: %.c
	$(CC) $(CCFLAGS) -c -o $@ $<

libcoro.a: $(OBJECTS)
	ld -r $(OBJECTS) -o $@

example: libcoro.o example.c
	$(CC) $(CCFLAGS) -o example example.c libcoro.o

.PHONY: clean
clean:
	$(RM) $(OBJECTS) libcoro.a example
