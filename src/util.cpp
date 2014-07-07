#include <util.hpp>

#include    <vector>
#include <algorithm>

namespace Utility {
    bool isKeyword(const std::string &Word) {
        const static std::vector<std::string> Keywords {
            "and", "as", "const", "do", "elif", "else",
            "extern", "for", "foreach", "function", "if",
            "import", "or", "prototype", "static", "var",
            "while"
        };

        return std::binary_search(Keywords.begin(), Keywords.end(), Word);
    }
}
