#include <util.hpp>

#include <sstream>

namespace Utility {
    double toFloat(std::string Value) {
             double        Altered;
        std::istringstream Stream(Value);

        Stream >> Altered;
        return Altered;
    }
}
