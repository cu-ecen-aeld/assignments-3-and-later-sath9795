all: writer

writer: writer.o
	$(CC) $(CFLAGS) -o writer writer.o

writer.o: writer.c
	$(CC) $(CFLAGS) -c -o writer.o writer.c

clean: 
	rm -f writer *.o

ifeq ($(CROSS_COMPILE),aarch64-none-linux-gnu-)
CC = aarch64-none-linux-gnu-gcc

endif

