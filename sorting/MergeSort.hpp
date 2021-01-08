#ifndef MERGESORT_H
#define MERGESORT_H

#include <functional>
#include <vector>

class MergeSort {
   public:
    template <typename Iter,
              typename Comp =
                  std::less<typename std::iterator_traits<Iter>::value_type>>
    static void Sort(Iter start, Iter end, Comp comp = Comp());

   private:
    template <typename Iter, typename Comp>
    static void Merge(Iter start, Iter mid, Iter end, Comp comp);
};

template <typename Iter, typename Comp>
inline void MergeSort::Merge(Iter start, Iter mid, Iter end, Comp comp) {
    std::size_t n1 = std::distance(start, mid);
    std::size_t n2 = std::distance(mid, end);
    std::vector<typename std::iterator_traits<Iter>::value_type> L(n1);
    std::copy(start, mid, L.begin());
    std::size_t i = 0;
    std::size_t j = 0;
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
inline void MergeSort::Sort(Iter start, Iter end, Comp comp) {
    std::size_t dist = std::distance(start, end);
    if (dist < 2) return;
    Iter mid = start + dist / 2;
    Sort(start, mid, comp);
    Sort(mid, end, comp);
    Merge(start, mid, end, comp);
}

#endif /* MERGESORT_H */
