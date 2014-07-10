#ifndef _ROOT_INCLUDE_LEXER_HPP
#define _ROOT_INCLUDE_LEXER_HPP

#include <istream>
#include <ostream>
#include  <string>
#include   <tuple>

namespace Token {
    enum Lexeme {
        Start = -2, Eof,
        Name, Keyword, String, Boolean, Number,
        LParen = '(', LBrace = '{', LBracket = '[', RParen = ')', RBrace = '}', RBracket = ']',
        Not = '!', Equals, NotEquals, GreaterThan = '>', LesserThan = '<', GreaterThanEquals, LesserThanEquals,
        Plus = '+', Minus = '-', Mult = '*', Div = '/', Assign = '=',
        Comma = ',', End = ';', Colon = ':', Dot = '.',
    };
}

namespace LexicalAnalyzer {
    class LexicalAnalyzer {
        private:
            std  ::istream *Stream;
            std  ::string   NameValue    = "",
                            KeywordValue = "",
                            StringValue  = "",
                            BoolValue    = "";
                   double   NumberValue  = 0.0;
                   long     LineNumber   = 0,
                            LineColumn   = 0;
            Token::Lexeme   CachedValue  = Token::Start;

            char getChar();
            void putBack(char);

        public:
             LexicalAnalyzer(std::istream*);
            ~LexicalAnalyzer();

            Token::Lexeme          getLexeme  ();
            std  ::string          getName    () const;
            std  ::string          getKeyword () const;
            std  ::string          getString  () const;
            std  ::string          getBool    () const;
                   double          getNumber  () const;
            std  ::tuple<int, int> getLocation() const;
            Token::Lexeme          flushCache () const;

            operator bool() const;
    };

    typedef LexicalAnalyzer lexer;
}

std::ostream& operator<<(std::ostream&, const LexicalAnalyzer::LexicalAnalyzer&);

namespace lexer = LexicalAnalyzer;

#endif
