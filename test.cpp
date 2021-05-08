#include "binary_tree/bst.hpp"
#include "sorting/BubbleSort.hpp"
#include "sorting/MergeSort.hpp"
#include "sorting/QuickSort.hpp"
#include "utils/IO.hpp"
#include "utils/Random.hpp"
#include "utils/Timer.hpp"
#include "utils/Validate.hpp"

template <typename Sorter, template <typename> class Comp,
          template <typename> class Validate, typename T>
void TestSorting(int num, int size, T val_min, T val_max) {
    Sorter sorter = Sorter();
    Comp<T> comp = Comp<T>();
    Validate<T> validate = Validate<T>();
    std::random_device rd;
    std::mt19937 mt(rd());

    std::cout << "Running sorting test with " << num << " random inputs.\n";
    std::cout << "contanier size = [1," << size << "], value =[" << val_min
              << "," << val_max << "]\n";
    utils::WallTimer timer;
    std::vector<std::vector<T>> failed_tests;
    for (int i = 0; i < num; ++i) {
        std::uniform_int_distribution<int> dist(1, size);
        using uniform_dist =
            typename uniform_distribution_selector<std::is_integral<T>::value,
                                                   T>::type;

        uniform_dist val_dist(val_min, val_max);
        std::vector<T> test(dist(mt));
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

void dfs(BinarySearchTree<int> &tree, std::size_t index) {
    if (!tree.Valid(index)) {
        return;
    }
    std::cout << tree.At(index) << " ";
    dfs(tree, tree.Left(index));
    dfs(tree, tree.Right(index));
}

#include <condition_variable>
#include <mutex>
#include <thread>

std::condition_variable cond;
std::mutex mutex;
int num = 0;

void print(char a, int cnt) {
    std::unique_lock<std::mutex> q(mutex);
    for (int i = 0; i < cnt; ++i) {
        while (num % 3 != a - 'A') cond.wait(q);
        std::cout << a << "\n";
    }
    num++;
    cond.notify_all();
}

int partition(std::vector<int> &arr, int start, int end) {
    int key = arr[start];
    --end;
    while (start < end) {
        while (start < end && arr[end] > key) {
            --end;
        }
        if (start < end) {
            arr[start] = arr[end];
        }
        while (start < end && arr[start] <= key) {
            ++start;
        }
        if (start < end) {
            arr[end] = arr[start];
        }
    }
    arr[start] = key;
    return start;
}

int findMedian(std::vector<int> &arr) {
    int left = 0;
    int right = arr.size();
    int mid = right >> 1;
    while (true) {
        int k = partition(arr, left, right);
        if (k < mid) {
            left = k + 1;
        } else if (k > mid) {
            right = k;
        } else {
            return arr[mid];
        }
    }
}

int main() {
    int count = 2;
    while (count--) {
        std::thread t1(print, 'A', 2);
        std::thread t3(print, 'B', 3);
        std::thread t2(print, 'C', 3);
        t1.join();
        t2.join();
        t3.join();
    }
    std::cout << std::endl;
    TestSorting<BubbleSort, std::less, std::less_equal>(900, 20, -324.2, 700.4);
    TestSorting<BubbleSort, std::greater, std::greater_equal>(900, 20, -324,
                                                              700);

    TestSorting<MergeSort, std::less, std::less_equal>(900, 20, -324.2, 700.4);
    TestSorting<MergeSort, std::greater, std::greater_equal>(900, 20, -324,
                                                             700);
    TestSorting<QuickSort, std::less, std::less_equal>(900, 20, -324, 700);
    TestSorting<QuickSort, std::greater, std::greater_equal>(900, 20, -324,
                                                             700);
    std::vector<int> t{11, 12, 10, 2, 3, 4, 15, 2, 4, 1, 0};
    std::cout << findMedian(t) << std::endl;
    utils::PrintVector(t.begin(), t.end());
    return 0;
}
