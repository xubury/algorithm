#include <random>

#include "sorting/MergeSort.hpp"
#include "sorting/QuickSort.hpp"
#include "utils/IO.hpp"
#include "utils/Timer.hpp"
#include "utils/Validate.hpp"

template <typename T, typename T2>
void TestSorting(int num, int size, T val_min, T val_max, T2 func) {
    std::random_device rd;
    std::mt19937 mt(rd());

    std::cout << "Running merge sort of total " << num
              << " random tests input\n";
    std::cout << "contanier size = [1," << size << "], value =[" << val_min
              << "," << val_max << "]\n";
    WallTimer timer;
    std::vector<std::vector<T>> failed_tests;
    for (int i = 0; i < num; ++i) {
        std::uniform_int_distribution<T> dist(1, size);
        std::uniform_int_distribution<T> val_dist(val_min, val_max);
        std::vector<int> test(dist(mt));
        for (auto &t : test) {
            t = val_dist(mt);
        }
        func(test.begin(), test.end(), std::less<T>());
        if (!ValidateOrder(test.begin(), test.end())) {
            failed_tests.emplace_back(test);
        }
    }
    std::cout << "Test Finished, took " << timer.GetElapsedMS()
              << " millisecond.\n";
    std::cout << "Test result:\n Passed:" << num - failed_tests.size() << "/"
              << num << "\n";
    if (!failed_tests.empty()) {
        std::cout << "Failing test:\n";
    }
    for (auto &test : failed_tests) {
        io::PrintVector(test.begin(), test.end());
    }
    std::flush(std::cout);
}

int main() {
    TestSorting(100, 20, -324, 700,
                &MergeSort::Sort<std::vector<int>::iterator>);
    TestSorting(100, 20, -324, 700,
                &QuickSort::Sort<std::vector<int>::iterator>);
    return 0;
}
