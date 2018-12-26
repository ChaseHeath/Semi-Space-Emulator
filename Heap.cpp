#include "Heap.h"
#include <ostream>

namespace gc {

Heap::Heap(std::size_t n) {
    memoryPool.reserve(n);
}

std::size_t Heap::size() const {
    return memoryPool.size();
}

std::size_t Heap::capacity() const {
    return memoryPool.capacity();
}
void Heap::setHeapTag(MemoryCell box)
{

    memoryPool.push_back(box.getTag());
}
CellTag Heap::getTag(MemoryCell box)
{
	return (*box.getPointer()).getTag();
}
void Heap::setNull()
{
	for (int i = 0; i < memoryPool.size(); i++)
	{
		memoryPool[i].setNull();
	}
}
CellTag Heap::getTag(int64_t i)
{
	return memoryPool[i].getTag();
}
void Heap::setHeapValue(MemoryCell box)
{
    memoryPool.push_back(box);
}
int64_t Heap::getValue(MemoryCell box)
{
	for (int i = 0; i < 9; i++)
	{
		if (box.getPointer() == &memoryPool[i])
			return memoryPool[i + 1].getValue();
	}
}
MemoryCell Heap::setPointer(MemoryCell box)
{
	for (int i = 0; box.getPointer() != memoryPool[i].getPointer(); i++)
	{
		if (box.getPointer() == memoryPool[i].getPointer())
		{
			box.setPointer(memoryPool[i].getPointer());
			return box;
		}
	}

}
MemoryCell* Heap::getHeap()
{
   return &memoryPool.back();
}
MemoryCell* Heap::getCertainHeap(int64_t i)
{
   return &memoryPool[i];
}
void Heap::getSpecificHeap(int64_t i)
{
	memoryPool.push_back(memoryPool[i]);
}
void Heap::getPointer(MemoryCell box)
{
memoryPool.push_back(box.getPointer());
}
void Heap::setFirst(MemoryCell* p1, MemoryCell* p2)
{
	auto itr = memoryPool.begin();
	for (; itr != memoryPool.end(); itr++)
	{
		if (p2 == &(*itr))
		{
			(*(itr + 1)).setPointer(p2);
			break;
		}
	}
}
void Heap::setSecond(MemoryCell* p1, MemoryCell* p2)
{
	auto itr = memoryPool.begin();
	for (; itr != memoryPool.end(); itr++)
	{
		if (p2 == &(*itr))
		{
			(*(itr + 2)).setPointer(p2);
			break;
		}
	}
}
MemoryCell* Heap::setSecondStack(MemoryCell* p2)
{
	auto itr = memoryPool.begin();
	for (; itr != memoryPool.end(); itr++)
	{
		if (p2 == &(*itr))
			return (*(itr + 2)).getPointer();
	}
}
MemoryCell* Heap::setFirstStack(MemoryCell* p1)
{
	auto itr = memoryPool.begin();
	for (; itr != memoryPool.end(); itr++)
	{
		if (p1 == &(*itr))
			return (*(itr + 1)).getPointer();
	}
}
int64_t Heap::add(MemoryCell *p1, MemoryCell *p2)
{
	int64_t sum = 0;
	auto itr = memoryPool.begin();
	for (; itr != memoryPool.end(); itr++)
	{
		if (p1 == &(*itr)) {
			sum += (*(itr + 1)).getValue();
		}
		if (p2 == &(*itr)) {
			sum += (*(itr + 1)).getValue();
		}
	}
	return sum;
}
int64_t Heap::garc(MemoryCell box)
{
	for (int i = 0; box.getPointer() != &memoryPool[i]; i++)
	{
		if (box.getPointer() == &memoryPool[i])
			return memoryPool[i+1].getValue();
	}
}
int64_t Heap::garc2(MemoryCell box)
{
	for (int i = 0; box.getPointer() != &memoryPool[i]; i++)
	{
		if (box.getPointer() == &memoryPool[i])
			return i + 2;
	}
}
std::vector<MemoryCell> Heap::get()
{
	return memoryPool;
}
MemoryCell* Heap::search1(std::vector<MemoryCell> memoryPool2, MemoryCell box)
{
	int i = 0, j = 0;
	for(; i < memoryPool2.size(); i++)
	{
		if(box.getPointer() == &memoryPool2[i])
			break;
	}
	if(memoryPool2[i].getTag() == CellTag::Int)

	for(;j < memoryPool.size(); j++)
	{
		if(memoryPool[j].getTag() == memoryPool2[i].getTag() && memoryPool[j].getTag() == CellTag::Int)
			if(memoryPool[j+1].getValue() == memoryPool2[i+1].getValue())
				return &memoryPool[j];
	}
}
std::ostream& operator<<(std::ostream& os, const Heap& heap) {
    os << "Heap( ";
    auto const& memPool = heap.memoryPool;
    auto printHeapCell = [&os](const MemoryCell& cell) {
        os << std::hex << &cell << ": " << std::dec;
        os << cell;
    };

    if (!memPool.empty()) {
        printHeapCell(memPool.front());
        for (std::size_t i = 1, e = memPool.size(); i < e; ++i) {
            os << "; ";
            printHeapCell(memPool[i]);
        }
    }
    os << " )";

    return os;
}
}