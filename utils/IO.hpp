#ifndef IO_HPP
#define IO_HPP

#include <iostream>
#include <vector>

namespace utils {

template <typename Iter>
inline void PrintVector(Iter begin, Iter end) {
    std::cout << "[";
    while (begin != end) {
        char sep = begin + 1 != end ? ' ' : ']';
        std::cout << *begin++ << sep;
    }
    std::cout << std::endl;
}

}  // namespace utils

#endif
