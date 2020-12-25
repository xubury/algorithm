#include <functional>
#include <vector>

class Sorter {
   public:
    template <typename Iter,
              typename Comp =
                  std::less<typename std::iterator_traits<Iter>::value_type>>
    static void MergeSort(Iter start, Iter end, Comp comp = Comp());

   private:
    template <typename Iter,
              typename Comp =
                  std::less<typename std::iterator_traits<Iter>::value_type>>
    static void Merge(Iter start, Iter mid, Iter end, Comp comp);
};

template <typename Iter, typename Comp>
inline void Sorter::Merge(Iter start, Iter mid, Iter end, Comp comp) {
    std::size_t i = 0;
    std::size_t j = 0;
    std::size_t n1 = std::distance(start, mid);
    std::size_t n2 = std::distance(mid, end);
    std::vector<typename std::iterator_traits<Iter>::value_type> L(n1);
    for (; i < n1; ++i) {
        L[i] = *(start + i);
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
inline void Sorter::MergeSort(Iter start, Iter end, Comp comp) {
    std::size_t dist = std::distance(start, end);
    if (dist < 2) return;
    Iter mid = start + dist / 2;
    MergeSort(start, mid, comp);
    MergeSort(mid, end, comp);
    Merge(start, mid, end, comp);
}
