#ifndef _ROOT_INCLUDE_PARSER_HPP
#define _ROOT_INCLUDE_PARSER_HPP

#include <string>

#include <lexer.hpp>
#include  <util.hpp>

namespace Token {
    class Token {
        private:
            Lexeme TokenType;
            std::string Name;
            util::Any Value;
            int LineNumber;
            int LineColumn;

        public:
            Token(
                    Lexeme _TokenType = Start,
                    std::string _Name = "",
                    util::Any _Value = 0,
                    int _LineNumber = 0,
                    int _LineColumn = -1
            ) :     TokenType(_TokenType),
                    Name(_Name),
                    Value(_Value),
                    LineNumber(_LineNumber),
                    LineColumn(_LineColumn) {}
    };
}

#endif
