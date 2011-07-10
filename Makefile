ifeq ($(CC),clang)
CXX = clang
LDFLAGS = -lstdc++
else
CXX = g++
CC = g++
endif

CXXFLAGS = -g -Wall -std=gnu++0x

OBJS = main.o file_bank.o bank.o account.o transaction.o

EXES = main

all: $(EXES)

main: $(OBJS)

clean:
	rm -f $(OBJS) $(EXES)
