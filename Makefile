CC=gcc
CFLAGS=-Wall -ggdb -std=c99
TARGETS=match counts

all: $(TARGETS)

counts: counts.c
	$(CC) $(CFLAGS) -o $@ $^

match: match.c linked_list.c linked_list.h stack.c stack.h
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -f *.o *~ $(TARGETS) a.out