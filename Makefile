TARGET := build/algorithm

CXX ?= g++
CXXWARNINGS ?= -Wall -Wextra -Wundef -pedantic
CXXFEATURES ?= -std=c++11  -pthread
CXXFLAGS ?= ${CXXWARNINGS} ${CXXFEATURES} -g

COMPILE.cpp = ${CXX} ${CXXFLAGS} ${CPPFLAGS} -c
LINK.o = ${CXX} ${LDFLAGS}
.DEFAULT_GOAL := ${TARGET}

SOURCES := $(wildcard [^_]*.cpp)

OBJS := $(patsubst %.cpp, build/%.o, $(SOURCES))

# How to link example from example.o and other files.
%: %.o
	${LINK.o} -o $@ $^ ${LDLIBS}

# How to compile example.o from example.cc.
$(OBJS): ${SOURCES}
	 ${COMPILE.cpp} -o $@ $<


${TARGET}: ${OBJS} 
	${LINK.o} $^ -lpthread ${LDLIBS} -o $@ 

clean:
	${RM} ${TARGET} ${OBJS} 

.PHONY: clean
