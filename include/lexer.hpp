#ifndef _ROOT_INCLUDE_LEXER_HPP
#define _ROOT_INCLUDE_LEXER_HPP

#include <istream>

namespace Token {
    enum Token {
        Start = -2, Eof,
        Name, Keyword, String, Boolean, Number, Float,
        LParen = '(', LBrace = '{', LBracket = '[', RParen = ')', RBrace = '}', RBracket = ']',
        Not = '!', Equals, NotEquals, GreaterThan = '>', LesserThan = '<', GreaterThanEquals, LesserThanEquals,
        Plus = '+', Minus = '-', Mult = '*', Div = '/', Assign = '=',
        Comma = ',', End = ';', Colon = ':', Dot = '.',
    };
}

Token::Token getToken(std::istream*);

#endif
