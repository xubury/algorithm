#include <iostream>
#include <vector>

namespace io {

template <typename Iter>
inline void PrintVector(Iter begin, Iter end) {
    while (begin != end) {
        std::cout << *begin++ << " ";
    }
    std::cout << std::endl;
}

}  // namespace io
