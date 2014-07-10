#include <iostream>
#include  <fstream>
#include  <sstream>
#include   <vector>
#include   <string>

#include <lexer.hpp>
#include  <util.hpp>

int main(int argc, char *argv[]) {
    std::vector<std::string> Arguments(argv, argv + argc);
    lexer::lexer Lexer;

    switch(argc) {
        case 1:
            Lexer.set(&std::cin);
            break;

        case 2:
            Lexer.set(std::ifstream(&Arguments[1]);
            break;

        case 3:
            if(Arguments[1] == "-c") {
                Lexer.set(std::istringstream(&Arguments[2]));
                break;
            }

        default:
            std::cerr<<"error: invalid arguments."<< std::endl;
            return 0;
    }

    Token::Lexeme CurrentToken = Token::Start;

    while(Lexer) {
        CurrentToken = Lexer.getLexeme();
        std::cout<< Lexer << std::endl;
        util::upause();
        util::uclear();
    }

    if(Stream != &std::cin) {
        delete Stream;
    }

    return 0;
}
