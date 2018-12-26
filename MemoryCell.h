#pragma once

#include <cstdint>
#include <iosfwd>
#include <stdexcept>

namespace gc {

enum class CellType { Null, Tag, Value, Pointer };

enum class CellTag { Int, Pair };

class RuntimeTypeError : std::exception {};

class MemoryCell {
private:
    CellType type;
    std::intptr_t data;

public:
    MemoryCell() : type(CellType::Null), data(0) {}
    MemoryCell(CellTag t)
        : type(CellType::Tag), data(static_cast<std::intptr_t>(t)) {}
    MemoryCell(std::int64_t value)
        : type(CellType::Value), data(static_cast<std::intptr_t>(value)) {}
    MemoryCell(MemoryCell* ptr)
        : type(CellType::Pointer), data(reinterpret_cast<std::intptr_t>(ptr)) {}

    CellType getCellType() const { return type; }
    bool isNullCell() const { return type == CellType::Null; }
    bool isTagCell() const { return type == CellType::Tag; }
    bool isValueCell() const { return type == CellType::Value; }
    bool isPointerCell() const { return type == CellType::Pointer; }

    CellTag getTag() const;
    void setTag(CellTag);
    std::int64_t getValue() const;
    void setValue(std::int64_t);
    MemoryCell* getPointer() const;
    void setPointer(MemoryCell*);
    void setNull();
};

std::ostream& operator<<(std::ostream&, CellTag);
std::ostream& operator<<(std::ostream&, CellType);
std::ostream& operator<<(std::ostream&, const MemoryCell&);
}