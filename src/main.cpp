#include <iostream>
#include  <fstream>
#include  <sstream>
#include   <vector>
#include   <string>

#include <lexer.hpp>
#include  <util.hpp>

int main(int argc, char *argv[]) {
    lexer::lexer  Lexer(argc, argv);
    Token::Lexeme CurrentToken = Token::Start;

    while(Lexer) {
        CurrentToken = Lexer.getLexeme();
        std::cout<< Lexer << std::endl;
        util::pause();
        util::clear();
    }
    return 0;
}
