#ifndef BUBBLESORT_H
#define BUBBLESORT_H

#include <functional>
#include <iostream>

class BubbleSort {
   public:
    template <typename Iter,
              typename Comp =
                  std::less<typename std::iterator_traits<Iter>::value_type>>
    static void Sort(Iter start, Iter end, Comp comp = Comp());
};

template <typename Iter, typename Comp>
inline void BubbleSort::Sort(Iter start, Iter end, Comp comp) {
    std::size_t size = std::distance(start, end);
    for (std::size_t i = 0; i < size; ++i) {
        for (std::size_t j = 0; j < size - i - 1; ++j) {
            if (!comp(start[j], start[j + 1])) {
                std::swap(start[j], start[j + 1]);
            }
        }
    }
}

#endif /* BUBBLESORT_H */
