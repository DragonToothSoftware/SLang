#include <lexer.hpp>

#include    <string>
#include    <vector>
#include <algorithm>
#include  <iterator>
#include    <cctype>

bool isKeyword(const std::string&);

namespace {
    std::string NameValue   = "",
                StringValue = "",
                BoolValue   = "";
         double NumberValue = 0.0;
}

Token::Token getToken(std::istream *Stream) {
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

        case '0': case '1': case '2': case '3':
        case '4': case '5': case '6': case '7':
        case '8': case '9': {
            std::string NumberStr(1, Current);

            for(auto Next : *Stream) {
                if(!isdigit(Next) || Next != '.') {
                    break;
                }

                NumberStr += Next;
            }
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

                NameValue = Temp;
                return isKeyword(Temp) ? Token::Keyword : Token::Name;
            }
        }
    }
}

bool isKeyword(const std::string &Word) {
    const static std::vector<std::string> Keywords {
        "and", "as", "const", "do", "elif", "else",
        "extern", "for", "foreach", "function", "if",
        "import", "or", "prototype", "static", "var",
        "while"
    };

    return std::binary_search(Keywords.begin(), Keywords.end(), Word);
}
