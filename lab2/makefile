
CC = g++ 
CFLAGS = -Wall -std=c++98
BIN = Prog2

all: $(BIN)

Prog2: Prog2.cpp Support.h Support.cpp
	$(CC) $(CFLAGS) -o $@ Prog2.cpp Support.cpp

clean:
	rm -f $(BIN)
