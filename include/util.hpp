#ifndef _ROOT_INCLUDE_UTIL_HPP
#define _ROOT_INCLUDE_UTIL_HPP

#include <functional>

namespace utility {
    template<typename T, typename I> void forEachDigit(T, T, std::function<void(I)>);
}

namespace util = utility;

#endif
