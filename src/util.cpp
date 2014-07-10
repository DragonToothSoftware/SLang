#include <util.hpp>

#include    <vector>
#include <algorithm>

#ifdef _WIN32
    #include <windows.h>

#else
    #include <iostream>
    #include <unistd.h>
    #include <term.h>
    #include <stdio.h>
    #include <termios.h>
#endif

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

    void uclear() {
    #ifdef _WIN32
        HANDLE                     hStdOut;
        CONSOLE_SCREEN_BUFFER_INFO csbi;
        DWORD                      count;
        DWORD                      cellCount;
        COORD                      homeCoords = { 0, 0 };

        hStdOut = GetStdHandle( STD_OUTPUT_HANDLE );

        if(hStdOut == INVALID_HANDLE_VALUE || !GetConsoleScreenBufferInfo( hStdOut, &csbi )) return;

        cellCount = csbi.dwSize.X * csbi.dwSize.Y;

        if(!FillConsoleOutputCharacter(hStdOut, (TCHAR) ' ', cellCount, homeCoords, &count)) return;
        if(!FillConsoleOutputAttribute(hStdOut, csbi.wAttributes, cellCount, homeCoords, &count)) return;

        SetConsoleCursorPosition(hStdOut, homeCoords);

    #else
        if(!cur_term) {
            int result;
            setupterm(NULL, STDOUT_FILENO, &result);
            if(result <= 0) return;
        }

        putp(tigetstr("clear"));
    #endif
    }

    void upause(std::string Prompt) {
    #ifdef _WIN32
        DWORD        mode;
        HANDLE       hstdin;
        INPUT_RECORD inrec;
        DWORD        count;

        hstdin = GetStdHandle(STD_INPUT_HANDLE);

        if(hstdin == INVALID_HANDLE_VALUE || !GetConsoleMode(hstdin, &mode) || !SetConsoleMode(hstdin, 0)) return 0;
 
        WriteConsole(GetStdHandle(STD_OUTPUT_HANDLE),  Prompt.c_str(), lstrlen(Prompt.c_str()), &count, NULL);
        FlushConsoleInputBuffer( hstdin );

        do ReadConsoleInput(hstdin, &inrec, 1, &count); while ((inrec.EventType != KEY_EVENT) || inrec.Event.KeyEvent.bKeyDown);

        SetConsoleMode(hstdin, mode);
        return inrec.Event.KeyEvent.wVirtualKeyCode;

    #else
        struct termios initial_settings;
        struct termios settings;
        unsigned char  keycodes[18];
        int            count;

        tcgetattr(STDIN_FILENO, &initial_settings);
        settings = initial_settings;

        settings.c_cc[VTIME] = 1;
        settings.c_cc[VMIN] = 18;
        settings.c_iflag &= ~(IXOFF);
        settings.c_lflag &= ~(ECHO | ICANON);
        tcsetattr(STDIN_FILENO, TCSANOW, &settings);

        std::cout<< Prompt << std::endl;
        count = read(0, (void*)keycodes, 18);

        tcsetattr(STDIN_FILENO, TCSANOW, &initial_settings);
    #endif
    }
}
