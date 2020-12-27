#include <random>

#include "sorting/MergeSort.hpp"
#include "sorting/QuickSort.hpp"
#include "utils/IO.hpp"
#include "utils/Timer.hpp"
#include "utils/Validate.hpp"

template <typename Sorter, template <typename> class Comp,
          template <typename> class Validate, typename T>
void TestSorting(int num, int size, T val_min, T val_max,
                 Sorter sorter = Sorter(), Comp<T> comp = Comp<T>(),
                 Validate<T> validate = Validate<T>()) {
    std::random_device rd;
    std::mt19937 mt(rd());

    std::cout << "Running sorting test with " << num << " random inputs.\n";
    std::cout << "contanier size = [1," << size << "], value =[" << val_min
              << "," << val_max << "]\n";
    utils::WallTimer timer;
    std::vector<std::vector<T>> failed_tests;
    for (int i = 0; i < num; ++i) {
        std::uniform_int_distribution<int> dist(1, size);
        std::uniform_int_distribution<int> val_dist(val_min, val_max);
        std::vector<int> test(dist(mt));
        for (auto &t : test) {
            t = val_dist(mt);
        }
        sorter.Sort(test.begin(), test.end(), comp);
        if (!utils::ValidateOrder(test.begin(), test.end(), validate)) {
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
        utils::PrintVector(test.begin(), test.end());
    }
    std::flush(std::cout);
}

int main() {
    TestSorting<MergeSort, std::less, std::less_equal>(100, 20, -324, 700);
    TestSorting<MergeSort, std::greater, std::greater_equal>(100, 20, -324,
                                                             700);
    TestSorting<QuickSort, std::less, std::less_equal>(100, 20, -324, 700);
    TestSorting<QuickSort, std::greater, std::greater_equal>(100, 20, -324,
                                                             700);
    std::vector<int> t{0, 1};
    MergeSort::Sort(t.begin(), t.end());

    return 0;
}
