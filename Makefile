ifeq ($(CC),clang)
CXX = clang
LDFLAGS = -lstdc++
else
CXX = g++
CC = g++
endif

CXXFLAGS = -g -Wall -std=gnu++0x

OBJS = moneycl.o file_bank.o bank.o account.o transaction.o

EXES = moneycl

all: $(EXES)

moneycl: $(OBJS)

clean:
	rm -f $(OBJS) $(EXES)
