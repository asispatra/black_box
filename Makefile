TARGETS=network thread

CC=g++
CFLAGS=-Wall -Wextra -Wno-unused-parameter

INCLUDE=include
SRC=src
OBJ=obj
LIBS=-lpthread

OBJS = $(patsubst %,$(OBJ)/%,$(TARGETS))

.PHONY: all clean

all: $(OBJS)
	$(CC) main.cpp -o main $^ -I $(INCLUDE) $(LIBS)

$(OBJ)/%: $(SRC)/%.c
	$(CC) $(CFLAGS) -c -o $@ $< -I $(INCLUDE)

clean:
	rm main $(OBJ)/*
