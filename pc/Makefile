ifeq ($(CC),clang)
CXX = clang
LDFLAGS = -lstdc++
else
CXX = g++
CC = g++
endif

LOCAL_INCLUDES = -I../basic-framework/

CXXFLAGS = -g -Wall -std=gnu++0x $(LOCAL_INCLUDES)

OBJS = moneycl.o ../basic-framework/libmoney.a

EXES = moneycl

all: $(EXES)

moneycl: $(OBJS)

clean:
	rm -f *.o $(EXES)
