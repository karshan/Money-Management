ifeq ($(CC),clang)
CXX = clang
LDFLAGS = -lstdc++
else
CXX = g++
CC = g++
endif

CXXFLAGS = -g -Wall -std=gnu++0x

OBJS = file_bank.o bank.o account.o transaction.o

OUTPUT = libmoney.a

all: $(OUTPUT)

libmoney.a: $(OBJS)
	ar -cvq libmoney.a $(OBJS)

clean:
	rm -f $(OBJS) $(OUTPUT)
