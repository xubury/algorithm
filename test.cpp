#include <random>

#include "sorting/MergeSort.hpp"
#include "utils/IO.hpp"
#include "utils/Validate.hpp"

void TestMergeSort(int num, int size, int val_min, int val_max) {
    std::random_device rd;
    std::mt19937 mt(rd());

    std::cout << "Running merge sort of total " << num
              << " random tests input\n";
    std::cout << "contanier size = [0," << size << "], value =[" << val_min
              << "," << val_max << "]\n";
    std::vector<std::vector<int>> failed_tests;
    for (int i = 0; i < num; ++i) {
        std::uniform_int_distribution<int> dist(1, size);
        std::uniform_int_distribution<int> val_dist(val_min, val_max);
        std::vector<int> test(dist(mt));
        for (auto &t : test) {
            t = val_dist(mt);
        }
        Sorter::MergeSort(test.begin(), test.end());
        if (!ValidateOrder(test.begin(), test.end())) {
            failed_tests.emplace_back(test);
        }
    }
    std::cout << "Test result:\n Passed:" << num - failed_tests.size() << "/"
              << num << "\n";
    if (!failed_tests.empty()) {
        std::cout << "Failing test:\n";
    }
    for (auto test : failed_tests) {
        io::PrintVector(test.begin(), test.end());
    }
    std::flush(std::cout);
}

int main() {
    TestMergeSort(10, 256, std::numeric_limits<int>::min(),
                  std::numeric_limits<int>::max());

    return 0;
}
