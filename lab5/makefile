
CC = g++
CFLAGS = -Wall -std=c++98
BIN = Prog5

all: $(BIN)

Prog5: Prog5.cpp Support.h Support.cpp
	$(CC) $(CFLAGS) -o $@ Prog5.cpp Support.cpp

clean:
	rm -f $(BIN)
