#include <random>

#include "sorting/MergeSort.hpp"
#include "sorting/QuickSort.hpp"
#include "utils/IO.hpp"
#include "utils/Timer.hpp"
#include "utils/Validate.hpp"

template <template <typename> class Comp, template <typename> class Validate,
          template <typename, typename> class Sorter, typename T>
void TestSorting(int num, int size, T val_min, T val_max,
                 Sorter<typename std::vector<T>::iterator, Comp<T>> sorter =
                     Sorter<typename std::vector<T>::iterator, Comp<T>>(),
                 Validate<T> validate = Validate<T>()) {
    std::random_device rd;
    std::mt19937 mt(rd());

    std::cout << "Running sorting test with " << num << " random inputs.\n";
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
    TestSorting<std::less, std::less_equal, MergeSort>(100, 20, -324, 700);
    TestSorting<std::greater, std::greater_equal, MergeSort>(100, 20, -324,
                                                             700);
    TestSorting<std::less, std::less_equal, QuickSort>(100, 20, -324, 700);
    TestSorting<std::greater, std::greater_equal, QuickSort>(100, 20, -324,
                                                             700);
    return 0;
}
