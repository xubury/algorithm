#include <random>

#include "sorting/MergeSort.hpp"
#include "sorting/QuickSort.hpp"
#include "utils/IO.hpp"
#include "utils/Timer.hpp"
#include "utils/Validate.hpp"

template <typename Comp, typename T, typename T2>
void TestSorting(int num, int size, T val_min, T val_max, T2 sorter,
                 Comp validate) {
    std::random_device rd;
    std::mt19937 mt(rd());

    std::cout << "Running sorting test of total " << num << " random input\n";
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
        sorter.Sort(test.begin(), test.end());
        if (!ValidateOrder(test.begin(), test.end(), validate)) {
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
                MergeSort<std::vector<int>::iterator, std::less<int>>(),
                std::less_equal<int>());
    TestSorting(100, 20, -324, 700,
                MergeSort<std::vector<int>::iterator, std::greater<int>>(),
                std::greater_equal<int>());
    TestSorting(100, 20, -324, 700,
                QuickSort<std::vector<int>::iterator, std::less<int>>(),
                std::less_equal<int>());
    TestSorting(100, 20, -324, 700,
                QuickSort<std::vector<int>::iterator, std::greater<int>>(),
                std::greater_equal<int>());
    return 0;
}
