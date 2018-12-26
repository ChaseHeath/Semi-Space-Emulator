#include "MemoryCell.h"

#include <ostream>

namespace gc {

CellTag MemoryCell::getTag() const {
    if (type != CellType::Tag)
        throw RuntimeTypeError();
    return static_cast<CellTag>(data);
}

void MemoryCell::setTag(CellTag tag) {
    type = CellType::Tag;
    data = static_cast<std::intptr_t>(tag);
}

std::int64_t MemoryCell::getValue() const {
    if (type != CellType::Value)
        throw RuntimeTypeError();
    return static_cast<std::int64_t>(data);
}

void MemoryCell::setValue(std::int64_t i) {
    type = CellType::Value;
    data = static_cast<std::intptr_t>(i);
}

MemoryCell* MemoryCell::getPointer() const {
    if (type != CellType::Pointer)
        throw RuntimeTypeError();
    return reinterpret_cast<MemoryCell*>(data);
}

void MemoryCell::setPointer(MemoryCell* ptr) {
    type = CellType::Pointer;
    data = reinterpret_cast<std::intptr_t>(ptr);
}

void MemoryCell::setNull() {
    type = CellType::Null;
    data = 0;
}

std::ostream& operator<<(std::ostream& os, CellTag tag) {
    switch (tag) {
        case CellTag::Int:
            os << "[Int]";
            break;
        case CellTag::Pair:
            os << "[Pair]";
            break;
    }
    return os;
}
std::ostream& operator<<(std::ostream& os, CellType type) {
    switch (type) {
        case CellType::Null:
            os << "NULL";
            break;
        case CellType::Value:
            os << "INT";
            break;
        case CellType::Tag:
            os << "TAG";
            break;
        case CellType::Pointer:
            os << "POINTER";
            break;
    }
    return os;
}

std::ostream& operator<<(std::ostream& os, const MemoryCell& cell) {
    os << "MemoryCell{ " << cell.getCellType();
    switch (cell.getCellType()) {
        case CellType::Null:
            break;
        case CellType::Value:
            os << " " << cell.getValue();
            break;
        case CellType::Tag:
            os << " " << cell.getTag();
            break;
        case CellType::Pointer:
            os << " " << std::hex << cell.getPointer() << std::dec;
            break;
    }
    os << " }";

    return os;
}
}