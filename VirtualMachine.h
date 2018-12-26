#pragma once

#include "Heap.h"
#include "Stack.h"

namespace gc {

class StackException : public std::exception {};

class VirtualMachine {
private:
    Stack stack;
    Heap heap;

public:
    VirtualMachine(std::size_t);

    // Allocate an int object on the heap and put a reference to it on the stack
    void pushInt(std::int64_t);
    // Pop the top two references on the stack and use them to create a pair
    // object on heap, then push the reference to the pair on the stack
    void pushPair();
    // Pop the top reference from the stack.
    void pop();
    // Duplicate the stack top
    void dup();
    // Pop the top reference, load the first component of its underlying object,
    // then put the result onto the stack
    void loadFirst();
    // Pop the top reference, load the second component of its underlying
    // object, then put the result onto the stack
    void loadSecond();
    // Pop the top reference and store it into the first component of the
    // underlying object of the new stack top
    void storeFirst();
    // Pop the top reference and store it into the second component of the
    // underlying object of the new stack top
    void storeSecond();
    // Pop the top two references on the stack, add them up, create a new int
    // object from the sum on the heap, and put a reference to the newly created
    // object on the stack
    void add();

    // Force the VM to perform garbage collection immediately
    void gc();
    // Get the MemoryCell reference at given stack address
    const MemoryCell& getStackReference(std::size_t) const;
    // Return the number of elements on the stack
    size_t getStackSize() const;
    // Return the current number of memory cells on the heap
    size_t getHeapSize() const;
    friend std::ostream& operator<<(std::ostream&, const VirtualMachine&);
};

std::ostream& operator<<(std::ostream&, const VirtualMachine&);
}
