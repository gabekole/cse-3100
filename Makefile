TARGETS=epidemic
CC=gcc
CFLAGS=-Wall -ggdb -std=c99

all : $(TARGETS)

$(TARGETS): %: %.c

clean: 
	@rm -f $(TARGETS) a.out *.o

