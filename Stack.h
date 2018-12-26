#pragma once

#include <iosfwd>
#include <vector>

namespace gc {
class MemoryCell;
using Stack = std::vector<MemoryCell*>;
std::ostream& operator<<(std::ostream&, const Stack&);
}
