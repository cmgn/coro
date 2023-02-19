CCFLAGS += -Wall -Werror -g
OBJECTS += yield.o coro.o

%.o: %.s
	as -o $@ $<

%.o: %.c
	$(CC) $(CCFLAGS) -c -o $@ $<

libcoro.o: $(OBJECTS)
	ld -r $(OBJECTS) -o $@

example: libcoro.o
	$(CC) $(CCFLAGS) -o example example.c libcoro.o

.PHONY: clean
clean:
	$(RM) $(OBJECTS) libcoro.o example
