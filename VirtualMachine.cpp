#include "VirtualMachine.h"

#include <ostream>

namespace gc {

VirtualMachine::VirtualMachine(std::size_t heapCapacity) : heap(heapCapacity) {}

void VirtualMachine::pushInt(std::int64_t value) {
    // Implement this function

    //If it tries to add an int to the heap and it is full, call the
    //garbage collector, if still full, throw OutOfMemoryException
	if(heap.size() + 2 > heap.capacity())
   	{												
    	gc();
	   	if(heap.size() + 2 > heap.capacity())
    		throw OutOfMemoryException();
	}
    MemoryCell box;
    CellTag tag = CellTag::Int;
    //Set the tag to the heap and push it onto the stack
    box.setTag(tag);
    heap.setHeapTag(box);
    stack.push_back(heap.getHeap());
    //Set the value of the Int added to the heap
    box.setValue(value);
    heap.setHeapValue(box);
}

void VirtualMachine::pushPair() {
    // Implement this function

    //
    if(stack.size() < 2)
    	throw StackException();
    else if(heap.size() + 3 > heap.capacity())
    {
    	gc();
    	if(heap.size() + 3 > heap.capacity())
    	throw OutOfMemoryException();
	}
    else
    {
	    MemoryCell box;
	    CellTag tag = CellTag::Pair;
    	MemoryCell* p1;
    	MemoryCell* p2;
    	p2 = stack.back();
    	p1 = stack.at(stack.size() - 2);
    	stack.pop_back();
   		stack.pop_back();
    	box.setTag(tag);
   	 	heap.setHeapTag(box);
  	  	stack.push_back(heap.getHeap());
    	box.setPointer(p1);
	    heap.getPointer(box);
    	box.setPointer(p2);
	    heap.getPointer(box);
	}
}

void VirtualMachine::pop() {
    // Implement this function
	if (stack.empty())
		throw StackException();
	else
		stack.pop_back();
}

void VirtualMachine::dup() {
    // Implement this function
    if(stack.empty())
    	throw StackException();
    else
		stack.push_back(stack[0]);
}

void VirtualMachine::loadFirst() {
    // Implement this function
    if(stack.empty())
    	throw StackException();
    else if(heap.getTag(stack.back()) != CellTag::Pair)
    	throw RuntimeTypeError();
    else{
		MemoryCell *p1 = stack.back();
		stack.pop_back();
		stack.push_back(heap.setFirstStack(p1));
		}
}

void VirtualMachine::loadSecond() {
    // Implement this function
     if(stack.empty())
    	throw StackException();
    else if(heap.getTag(stack.back()) != CellTag::Pair)
    	throw RuntimeTypeError();
    else
    {
		MemoryCell *p2 = stack.back();
		stack.pop_back();
		stack.push_back(heap.setSecondStack(p2));
	}
}

void VirtualMachine::storeFirst() {
    // Implement this function
     if(stack.size() < 2)
    	throw StackException();
    else if(heap.getTag(stack[1]) != CellTag::Pair)
    	throw RuntimeTypeError();
    else
    {
		MemoryCell *p2,*p1 = stack.back();
		MemoryCell box;
		stack.pop_back();
		p2 = stack.back();
		heap.setFirst(p1, p2);
	}
}

void VirtualMachine::storeSecond() {
    // Implement this function
     if(stack.empty())
    	throw StackException();
    else if(heap.getTag(stack.back()) != CellTag::Pair)
    	throw RuntimeTypeError();
    else
    {
		MemoryCell *p2, *p1 = stack.back();
		MemoryCell box;
		stack.pop_back();
		p2 = stack.back();
		heap.setSecond(p1, p2);
	}
}

void VirtualMachine::add() {
    // Implement this function
    if(stack.size() < 2)
    	throw StackException();
    else if(heap.getTag(stack.back()) != CellTag::Int || heap.getTag(stack.size() - 2) != CellTag::Int)
    	throw RuntimeTypeError();
    else if(heap.size() + 2 > heap.capacity())
   	{
    	gc();
	   	if(heap.size() + 2 > heap.capacity())
    		throw OutOfMemoryException();
	}
    else
    {
		MemoryCell box,box1;
		CellTag tag = CellTag::Int;
		MemoryCell *p1,*p2 = stack.back();
		stack.pop_back();
		p1 = stack.back();
		stack.pop_back();
		box1.setValue(heap.add(p1, p2));
		box.setTag(tag);
		heap.setHeapTag(box);
		stack.push_back(heap.getHeap());
		heap.setHeapValue(box1);
	}
}

void VirtualMachine::gc() {
    // Implement this function
	Heap heap2(heap.capacity());
	auto itr = stack.begin();
	int stackSize = stack.size();
	int stackCount[stackSize];
	int j = 0, i = 0;
	for (; itr != stack.end(); itr++)
	{
		MemoryCell *box, box3, box4;
		box = *itr;
		if ((*box).getTag() == CellTag::Int)
		{
			stackCount[j] = i;
			box3.setPointer(*(itr));
			heap2.setHeapTag(CellTag::Int);
			box4.setValue(heap.getValue(box3));
			heap2.setHeapValue(box4);
			i+= 2;
		}
		if ((*box).getTag() == CellTag::Pair)	
		{
			stackCount[j] = i;
			box3.setPointer(*(itr));
			heap2.setHeapTag(CellTag::Pair);
			i++;
		}
		j++;
	}
	stack.clear();
	heap = std::move(heap2);
	i = 0;
	while(i < stackSize)
	{
		stack.push_back(heap.getCertainHeap(stackCount[i]));
		i++;
	}
	/*
	for(int i = 0; i < heap.size(); i++)
	{
		if(heap.getTag(i) == CellTag::Int)
		{
			stack.push_back(heap.getCertainHeap(i));
			i++;
		}
		else if(heap.getTag(i) == CellTag::Pair)
		{
			stack.push_back(heap.getCertainHeap(i));
			i +=2;
		}
	}*/
}

const MemoryCell& VirtualMachine::getStackReference(std::size_t addr) const {
    if (stack.size() <= addr)
        throw StackException();
    return *stack[addr];
}

size_t VirtualMachine::getStackSize() const {
    return stack.size();
}

size_t VirtualMachine::getHeapSize() const {
    return heap.size();
}

std::ostream& operator<<(std::ostream& os, const VirtualMachine& vm) {
    os << vm.stack << '\n' << vm.heap << '\n';
    return os;
}
}
