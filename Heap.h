#pragma once

#include "MemoryCell.h"

#include <iosfwd>
#include <stdexcept>
#include <vector>

namespace gc {

class OutOfMemoryException : public std::exception {};

class Heap {
private:
    using SemiSpace = std::vector<MemoryCell>;
    SemiSpace memoryPool;

public:
    Heap(std::size_t);
    void setHeapTag(MemoryCell);
    void setHeapValue(MemoryCell);
    void getPointer(MemoryCell);
	void setNull();
	std::vector<MemoryCell> get();
	CellTag getTag(int64_t);
	CellTag getTag(MemoryCell);
    MemoryCell* getHeap();
    MemoryCell* getCertainHeap(int64_t);
	int64_t getValue(MemoryCell);
	void getSpecificHeap(int64_t);
	MemoryCell* search1(std::vector<MemoryCell>, MemoryCell);
	MemoryCell setPointer(MemoryCell);
	void setFirst(MemoryCell*, MemoryCell*);
	void setSecond(MemoryCell*, MemoryCell*);
	MemoryCell* setSecondStack(MemoryCell*);
	MemoryCell* setFirstStack(MemoryCell*);
	int64_t add(MemoryCell*, MemoryCell*);
	int64_t garc(MemoryCell);
	int64_t garc2(MemoryCell);
	std::size_t capacity() const;
    std::size_t size() const;

    friend std::ostream& operator<<(std::ostream&, const Heap&);
};

std::ostream& operator<<(std::ostream&, const Heap&);
}
