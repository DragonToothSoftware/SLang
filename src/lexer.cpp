#include <lexer.hpp>

#include    <string>
#include    <vector>
#include  <iterator>
#include    <cctype>

#include <util.hpp>

char getChar(std::istream*);

namespace {
    std::string NameValue    = "",
                KeywordValue = "",
                StringValue  = "",
                BoolValue    = "";
         double NumberValue  = 0.0;
         long   LineNumber   = 0,
                LineColumn   = 0;
}

Token::Lexeme getToken(std::istream *Stream) {
    static char Current = 0;

    do {
        Current = getChar(Stream);
    } while(isspace(Current));

    switch(Current) {
        case '=': return (Stream->peek() == '=' ? Stream->get(), Token::Equals            : Token::Assign);
        case '!': return (Stream->peek() == '=' ? Stream->get(), Token::NotEquals         : Token::Not);
        case '<': return (Stream->peek() == '=' ? Stream->get(), Token::LesserThanEquals  : Token::LesserThan);
        case '>': return (Stream->peek() == '=' ? Stream->get(), Token::GreaterThanEquals : Token::GreaterThan);

        case '(': case '[': case '{': case ')':
        case ']': case '}': case '+': case '-':
        case '*': case '/': case ',': case ';':
        case ':': case '.':
            return Token::Lexeme(Current);

        case '0' ... '9': {
            std::string NumberStr;

            do {
                NumberStr += Current;
            } while(((Current = getChar(Stream)) == '.') || (isdigit(Current)));

            Stream->putback(Current);
            NumberValue = stod(NumberStr);
            return Token::Number;
        }

        case '\"': case '\'': {
            char Start = Current;
            StringValue = "";

            do {
                StringValue += Current;
            } while((Current = getChar(Stream)) && Current != Start);

            StringValue += Current;
        }

        default: {
            if(isalpha(Current) || Current == '_') {
                std::string Temp (1, Current);

                while((Current = getChar(Stream)) && (isalnum(Current) || Current == '_')) {
                    Temp += Current;
                }

                Stream->putback(Current);

                if(Temp == "True" || Temp == "False") {
                    BoolValue = Temp;
                    return Token::Boolean;
                }

                else if(util::isKeyword(Temp)) {
                    KeywordValue = Temp;
                    return Token::Keyword;
                }

                NameValue = Temp;
                return Token::Name;
            }
        }
    }
}

char getChar(std::istream *Stream) {
    char Current = Stream->get();

    if(Current == '\n' || Current == '\r') {
        LineColumn = 0;
        LineNumber++;
    }

    else {
        LineColumn++;
    }

    return Current;
}

#include <iostream>

void lex_debug() {
    std::cout<<"Name Value: "<< NameValue << std::endl
             <<"Keyword Value: "<< KeywordValue << std::endl
             <<"String Value: "<< StringValue << std::endl
             <<"Bool Value: "<< BoolValue << std::endl
             <<"Number Value: "<< NumberValue << std::endl
             <<"Line Number/Column: "<< LineNumber <<"/"<< LineColumn << std::endl
             <<"--------------------------------------------------------------------------------"<< std::endl;
}
