#ifndef _ROOT_INCLUDE_UTIL_HPP
#define _ROOT_INCLUDE_UTIL_HPP

#include <string>

#include <any.hpp>

namespace Utility {
    class Any;

    bool isKeyword(const std::string&);
    void clear   ();
    void pause   (const std::string& ="");
}

namespace util = Utility;

#endif
