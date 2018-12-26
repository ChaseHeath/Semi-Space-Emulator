CXX = clang++
CPPFLAGS=-std=c++14 -g -O0 -Wall -Wextra

SRCS=main.cpp MemoryCell.cpp Stack.cpp Heap.cpp VirtualMachine.cpp
OBJS=$(SRCS:.cpp=.o)

all: gc

gc: $(OBJS)
	$(CXX) $^ -o $@

%.o: %.cpp %.h
	$(CXX) $(CPPFLAGS) -c $<

clean:
	rm -rf gc
	rm -rf $(OBJS)