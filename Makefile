CC=clang
CFLAGS=-std=gnu99 -g -Wall -Wextra -Werror \
       -Wno-unused-parameter -Wno-missing-field-initializers \
       -I src -I src/db
VPATH=src:src/db

PROGS=njuke_broker


.PHONY:all
all: $(PROGS)

# TODO: Add header and makefile deps.
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

njuke_broker: main.o njuke_types.o njuke_db_dummy.o
	$(CC) $(CFLAGS) $^ -o $@

.PHONY: clean
clean:
	$(RM) $(PROGS)
	$(RM) *.o
