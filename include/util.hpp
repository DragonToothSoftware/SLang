#ifndef _ROOT_INCLUDE_UTIL_HPP
#define _ROOT_INCLUDE_UTIL_HPP

#include <functional>

namespace utility {
    template<typename T, typename U, typename V> void forEachDigit(T, T, std::function<U(V)>);
}

namespace util = utility;

#endif
