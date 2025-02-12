
BINS = finddups


CFLAGS = -g -Wall -Wstrict-prototypes


LDFLAGS = -g


SRCS = finddups.c main.c
OBJS = finddups.o main.o

.PHONY: default
default: $(BINS)


finddups.o: finddups.c finddups.h
	$(CC) $(CFLAGS) -c finddups.c -o finddups.o

main.o: main.c finddups.h
	$(CC) $(CFLAGS) -c main.c -o main.o

# Link object files into the final executable
finddups: $(OBJS)
	$(CC) $(LDFLAGS) $(OBJS) -o finddups

.PHONY: clean
clean:
	rm -f core* *.o *~

.PHONY: immaculate
immaculate: clean
	rm -f $(BINS)

