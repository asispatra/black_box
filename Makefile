TARGETS=network thread

CC=gcc
CFLAGS=-Wall -Wextra

INCLUDE=include
SRC=src
OBJ=obj
LIBS=-lpthread

OBJS = $(patsubst %,$(OBJ)/%,$(TARGETS))

.PHONY: all clean

all: $(OBJS)
	$(CC) main.c -o main $^ -I $(INCLUDE) $(LIBS)

$(OBJ)/%: $(SRC)/%.c
	$(CC) $(CFLAGS) -c -o $@ $< -I $(INCLUDE)

clean:
	rm main $(OBJ)/*
