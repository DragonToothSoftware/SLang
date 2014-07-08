#include <iostream>
#include  <fstream>
#include  <sstream>
#include   <vector>
#include   <string>

#include <lexer.hpp>

int main(int argc, char *argv[]) {
    std::istream* Stream;
    std::vector<std::string> Arguments(argv, argv + argc);

    switch(argc) {
        case 1:
            Stream = &std::cin;
            break;

        case 2:
            Stream = new std::ifstream(Arguments[1]);
            break;

        case 3:
            if(Arguments[1] == "-c") {
                Stream = new std::istringstream(Arguments[2]);
                break;
            }

        default:
            std::cerr<<"error: invalid arguments."<< std::endl;
            return 0;
    }

    Token::Lexeme CurrentToken = Token::Start;

    while(*Stream) {
        CurrentToken = getToken(Stream);
        lex_debug();
    }

    if(Stream != &cin) {
        delete Stream;
    }

    return 0;
}
