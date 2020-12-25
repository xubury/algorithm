#include "sorting/MergeSort.hpp"
#include "utils/io.hpp"

int main() {
    std::vector<int> test_1{3, 546, 562, 1, 5, 7, 98, 2, 1, 6, 74, 74};
    Sorter::MergeSort(test_1.begin(), test_1.end());
    io::PrintVector(test_1.begin(), test_1.end());
    return 0;
}
