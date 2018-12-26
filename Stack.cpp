#include "Stack.h"

#include <ostream>

namespace gc {
std::ostream& operator<<(std::ostream& os, const Stack& stack) {
    os << "Stack( " << std::hex;
    if (!stack.empty()) {
        os << stack.front();
        for (std::size_t i = 1, e = stack.size(); i < e; ++i)
            os << "; " << stack[i];
    }
    os << std::dec << " )";

    return os;
}
}