
CC = g++
CFLAGS = -Wall -std=c++98
BIN = Prog3

all: $(BIN)

Prog3: Prog3.cpp Support.h Support.cpp
	$(CC) $(CFLAGS) -o $@ Prog3.cpp Support.cpp

clean:
	rm -f $(BIN)
