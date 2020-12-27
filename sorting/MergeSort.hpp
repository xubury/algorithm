#ifndef MERGESORT_H
#define MERGESORT_H

#include <functional>
#include <vector>

template <typename Iter,
          typename Comp =
              std::less<typename std::iterator_traits<Iter>::value_type>>
class MergeSort {
   public:
    void Sort(Iter start, Iter end, Comp comp = Comp());

   private:
    void Merge(Iter start, Iter mid, Iter end, Comp comp);
};

template <typename Iter, typename Comp>
inline void MergeSort<Iter, Comp>::Merge(Iter start, Iter mid, Iter end,
                                         Comp comp) {
    std::size_t i = 0;
    std::size_t j = 0;
    std::size_t n1 = std::distance(start, mid);
    std::size_t n2 = std::distance(mid, end);
    std::vector<typename std::iterator_traits<Iter>::value_type> L(n1);
    for (; i < n1; ++i) {
        L[i] = start[i];
    }
    i = 0;
    j = 0;
    while (i < n1 && j < n2) {
        if (comp(L[i], mid[j])) {
            *start++ = L[i++];
        } else {
            *start++ = mid[j++];
        }
    }
    while (i < n1) {
        *start++ = L[i++];
    }
    while (j < n2) {
        *start++ = mid[j++];
    }
}

template <typename Iter, typename Comp>
inline void MergeSort<Iter, Comp>::Sort(Iter start, Iter end, Comp comp) {
    std::size_t dist = std::distance(start, end);
    if (dist < 2) return;
    Iter mid = start + dist / 2;
    Sort(start, mid, comp);
    Sort(mid, end, comp);
    Merge(start, mid, end, comp);
}

#endif /* MERGESORT_H */
