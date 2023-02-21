CCFLAGS += -g
OBJECTS += yield_x64.o yield_arm.o coro.o

%.o: %.s
	$(CC) $(CCFLAGS) -o $@ -c -x assembler-with-cpp $<

%.o: %.c
	$(CC) $(CCFLAGS) -c -o $@ $<

libcoro.o: $(OBJECTS)
	ld -r $(OBJECTS) -o $@

example: libcoro.o example.c
	$(CC) $(CCFLAGS) -o example example.c libcoro.o

.PHONY: clean
clean:
	$(RM) $(OBJECTS) libcoro.o example
