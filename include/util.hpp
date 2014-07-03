#ifndef _ROOT_INCLUDE_UTIL_HPP
#define _ROOT_INCLUDE_UTIL_HPP

namespace utility {
    template<typename T, typename U>
    void forEachDigit(T Begin, T End, U Callback) {
        for(; Begin != End; Begin++) {
            if(isdigit(*Begin) || *Begin == '.') {
                Callback(*Begin);
            }
        }
    }
}

namespace util = utility;

#endif
