#include <random>

#include "sorting/MergeSort.hpp"
#include "utils/Validate.hpp"
#include "utils/io.hpp"

int main() {
    std::random_device rd;
    std::mt19937 mt(rd());

    // merge sort test
    for (int i = 0; i < 10; ++i) {
        std::uniform_int_distribution<int> dist(0, 256);
        std::uniform_int_distribution<int> val_dist(
            0, std::numeric_limits<int>::max());
        std::vector<int> test(dist(mt));
        for (auto &t : test) {
            t = val_dist(mt);
        }
        Sorter::MergeSort(test.begin(), test.end());
        if (ValidateOrder(test.begin(), test.end())) {
            std::cout << "Passed!\n";
        } else {
            io::PrintVector(test.begin(), test.end());
            std::cout << "Failed!\n";
        }
    }

    std::flush(std::cout);
    return 0;
}
