#include <iostream>

#include "sorting/MergeSort.hpp"

int main() {
    std::vector<int> test_1{3, 546, 562, 1, 5, 7, 98, 2, 1, 6, 74, 74};
    Sorter sort(test_1);
    sort.MergeSort(0, test_1.size());
    for (const auto t : test_1) {
        std::cout << t << " ";
    }
    std::cout << std::endl;
    return 0;
}
