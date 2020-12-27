#ifndef RANDOM_H
#define RANDOM_H

#include <random>

// Declare a class template
template <bool is_integral, typename T>
struct uniform_distribution_selector;

// Specialize for true
template <typename T>
struct uniform_distribution_selector<true, T> {
    using type = typename std::uniform_int_distribution<T>;
};

// Specialize for false
template <typename T>
struct uniform_distribution_selector<false, T> {
    using type = typename std::uniform_real_distribution<T>;
};

#endif /* RANDOM_H */
