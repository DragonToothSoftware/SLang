#include <lexer.hpp>

#include    <string>
#include    <vector>
#include  <iterator>
#include    <cctype>

#include <util.hpp>

bool isKeyword(const std::string&);

namespace {
    std::string NameValue    = "",
                KeywordValue = "",
                StringValue  = "",
                BoolValue    = "";
         double NumberValue  = 0.0;
}

Token::Lexeme getToken(std::istream* Stream) {
    static char Current = 0;

    do {
        Current = Stream->get();
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
            return Token::Token(Current);

        case '0' ... '9': {
            std::string NumberStr;

            do {
                NumberStr += Current;
            } while(((Current = Stream->get()) == '.') || (isdigit(Current)));

            Stream->putback(Current);
            NumberValue = stod(NumberStr);
            return Token::Number;
        }

        case '\"': case '\'': {
            char Start = Current;
            StringValue = "";

            do {
                StringValue += Current;
            } while((Current = Stream->get()) && Current != Start);

            StringValue += Current;
        }

        default: {
            if(isalpha(Current) || Current == '_') {
                std::string Temp (1, Current);

                while((Current = Stream->get()) && (isalnum(Current) || Current == '_')) {
                    Temp += Current;
                }

                Stream->putback(Current);

                if(Temp == "True" || Temp == "False") {
                    BoolValue = Temp;
                    return Token::Boolean;
                }

                if(util::isKeyword(Temp)) {
                    KeywordValue = Temp;
                    return Token::Keyword;
                }

                NameValue = Temp;
                return Token::Name;
            }
        }
    }
}

#include <iostream>

void lex_debug() {
    std::cout<<"Name Value: "<< NameValue << std::endl
             <<"Keyword Value: "<< KeywordValue << std::endl
             <<"String Value: "<< StringValue << std::endl
             <<"Bool Value: "<< BoolValue << std::endl
             <<"Number Value: "<< NumberValue << std::endl
             <<"--------------------------------------------------------------------------------"<< std::endl;
}
