# This Makefile is only used to build libmoney.a for x86 architectures, the 
# android build sytem uses the sources in this directory directly without 
# this makefile

# TODO: Add support for building an arm libmoney.a using android's 
# cross-compiler. You will need to change a lot of flags... so that it builds
# with the gnustl_static library provided in the ndk. (make android ?)

ifeq ($(CC),clang)
CXX = clang
LDFLAGS = -lstdc++
else
CXX = g++
CC = g++
endif

CXXFLAGS = -g -Wall

OBJS = file_bank.o bank.o account.o transaction.o

OUTPUT = libmoney.a

all: $(OUTPUT)

libmoney.a: $(OBJS)
	ar -cvq libmoney.a $(OBJS)

clean:
	rm -f $(OBJS) $(OUTPUT)
