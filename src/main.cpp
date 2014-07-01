#include  <iostream>
#include   <fstream>
#include   <sstream>

#include <lexer.hpp>

int main(int argc, char *argv[]) {
    static std::istream *Stream;

    switch(argc) {
        case 1:
            Stream = &std::cin;
            break;

        case 2:
            Stream = new std::ifstream(argv[1]);
            break;

        case 3:
            if(argv[1] == "-c") {
                Stream = new std::istringstream(argv[2]);
                break;
            }

        default:
            std::cerr<<"error: invalid arguments."<< std::endl;
            return 0;
    }

    Token::Token CurrentToken = Token::Start;

    while(*Stream) {
        CurrentToken = getToken(Stream);
        std::cout<< CurrentToken <<' '<< char(CurrentToken) << std::endl;
    }

    if(Stream != &std::cin) {
        delete Stream;
    }
}
