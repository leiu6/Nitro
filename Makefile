CC = gcc

CFLAGS := -Wall -Wextra -Wvla -Wpedantic -Werror -std=c11 -g -DNITRO_DEBUG_MEMORY
LDFLAGS := -lm -g

SRCS := main.c object.c value.c
DEPS := object.h value.h
OBJS := main.o object.o value.o

.PHONY: all

all: nitro

nitro: $(OBJS)
	$(CC) $(LDFLAGS) $^ -o nitro

.PHONY: clean

clean:
	rm -r *.o $(TARGET)

