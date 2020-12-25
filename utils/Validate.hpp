#ifndef VALIDATE_H
#define VALIDATE_H

#include <functional>
#include <iostream>

template <typename Iter, typename Comp = std::less_equal<
                             typename std::iterator_traits<Iter>::value_type>>
inline bool ValidateOrder(Iter start, Iter end, Comp comp = Comp()) {
    while (start != end - 1) {
        if (!comp(start[0], start[1])) {
            return false;
        }
        ++start;
    }
    return true;
}

#endif /* VALIDATE_H */
