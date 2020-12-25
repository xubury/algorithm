#include <vector>

class Sorter {
   public:
    Sorter(std::vector<int> &vec) : m_vec(vec){};
    void MergeSort(std::size_t lo, std::size_t hi);

   private:
    std::vector<int> &m_vec;
    void Merge(std::size_t lo, std::size_t mi, std::size_t hi);
};

inline void Sorter::Merge(std::size_t lo, std::size_t mi, std::size_t hi) {
    std::size_t i = 0;
    std::size_t j = 0;
    std::size_t n1 = mi - lo + 1;
    std::size_t n2 = hi - mi;
    std::vector<int> L(n1);
    std::vector<int> R(n2);
    for (; i < n1; ++i) {
        L[i] = m_vec[lo + i];
    }
    for (; j < n2; ++j) {
        R[j] = m_vec[mi + j + 1];
    }
    i = 0;
    j = 0;
    std::size_t k = lo;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            m_vec[k++] = L[i++];
        } else {
            m_vec[k++] = R[j++];
        }
    }
    while (i < n1) {
        m_vec[k++] = L[i++];
    }
    while (j < n2) {
        m_vec[k++] = R[j++];
    }
}

inline void Sorter::MergeSort(std::size_t lo, std::size_t hi) {
    if (lo >= hi) return;
    std::size_t mi = (lo + hi) / 2;
    MergeSort(lo, mi);
    MergeSort(mi + 1, hi);
    Merge(lo, mi, hi);
}
