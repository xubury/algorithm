#ifndef QUICKSORT_H
#define QUICKSORT_H

#include <functional>

template <typename Iter,
          typename Comp =
              std::less<typename std::iterator_traits<Iter>::value_type>>
class QuickSort {
   public:
    void Sort(Iter start, Iter end, Comp comp = Comp());

   private:
    Iter GetPivot(Iter start, Iter end, Comp comp);
};

template <typename Iter, typename Comp>
inline void QuickSort<Iter, Comp>::Sort(Iter start, Iter end, Comp comp) {
    if (std::distance(start, end) >= 2) {
        Iter pivot = GetPivot(start, end, comp);
        Sort(start, pivot, comp);
        Sort(pivot + 1, end, comp);
    }
}

template <typename Iter, typename Comp>
inline Iter QuickSort<Iter, Comp>::GetPivot(Iter start, Iter end, Comp comp) {
    typename std::iterator_traits<Iter>::value_type key = *start;
    std::size_t i = 0;
    std::size_t j = std::distance(start, end) - 1;
    while (i < j) {
        while (i < j && !comp(start[j], key)) {
            --j;
        }

        if (i < j) {
            start[i] = start[j];
        }

        while (i < j && comp(start[i], key)) {
            ++i;
        }

        if (i < j) {
            start[j] = start[i];
        }
    }
    start[i] = key;
    return start + i;
}

#endif /* QUICKSORT_H */
