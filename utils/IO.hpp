#ifndef IO_HPP
#define IO_HPP

#include <iostream>
#include <vector>

namespace utils {

template <typename Iter>
inline void PrintVector(Iter begin, Iter end) {
    while (begin != end) {
        std::cout << *begin++ << " ";
    }
    std::cout << std::endl;
}

}  // namespace utils

#endif
