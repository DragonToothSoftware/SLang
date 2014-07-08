#include <util.hpp>

#include    <vector>
#include <algorithm>

namespace Utility {
    bool isKeyword(const std::string &Word) {
        const static std::vector<std::string> Keywords {
            "and", "as", "clear" "const", "do", "elif",
            "else", "extern", "for", "foreach", "function",
            "if", "import", "or", "pause", "prototype",
            "static", "var", "while"
        };

        return std::binary_search(Keywords.begin(), Keywords.end(), Word);
    }

#ifdef _WIN32
    #include <windows.h>

#else
    #include <unistd.h>
    #include<term.h>
#endif

    void clear() {
    #ifdef _WIN32
        HANDLE                     hStdOut;
        CONSOLE_SCREEN_BUFFER_INFO csbi;
        DWORD                      count;
        DWORD                      cellCount;
        COORD                      homeCoords = { 0, 0 };

        hStdOut = GetStdHandle( STD_OUTPUT_HANDLE );

        if(hStdOut == INVALID_HANDLE_VALUE || !GetConsoleScreenBufferInfo( hStdOut, &csbi )) return;

        cellCount = csbi.dwSize.X *csbi.dwSize.Y;

        if(!FillConsoleOutputCharacter(hStdOut, (TCHAR) ' ', cellCount, homeCoords, &count)) return;
        if(!FillConsoleOutputAttribute(hStdOut, csbi.wAttributes, cellCount, homeCoords, &count)) return;

        SetConsoleCursorPosition( hStdOut, homeCoords );

    #else
        if(!cur_term) {
            int result;
            setupterm( NULL, STDOUT_FILENO, &result );
            if(result <= 0) return;
        }

        putp(tigetstr("clear"));
    #endif
    }
}
