#include <iostream>
#include  <fstream>
#include  <sstream>
#include   <string>
#include     <list>
#include   <cctype>

namespace Token {
    enum Token {
        Start = -1,
        Name,
        Keyword,
        Dot = '.',
        LParen = '(',
        RParen = ')',
        LBracket = '{',
        RBracket = '}',
        LIndex = '[',
        RIndex = ']',
        Equals,
        NotEquals,
        GreaterThan = '>',
        LesserThan = '<',
        GreaterThanEquals,
        LesserThanEquals,
        Plus = '+',
        Minus = '-',
        Mult = '*',
        Div = '/',
        Comma = ',',
        End = ';',
        Assign = '=',
        Not = '!',
        Colon = ':',
        String,
        Boolean,
        Number,
        Float,
    };
}

Token::Token getToken(std::istream*);
double toFloat(const std::string&);
bool isKeyword(const std::string&);

std::string NameValue = "", StringValue = "", BoolValue = "";
double FloatValue = 0.0;
int NumberValue = 0;


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
            if(argv[2] == "-c") {
                Stream = new std::istringstream(argv[3]);
                break;
            }

        default:
            std::cerr<<"error: invalid arguments."<< std::endl;
            return 0;
    }

    Token::Token CurrentToken = Token::Start;

    while(*Stream) {
        CurrentToken = getToken(Stream);
    }

    if(Stream != &std::cin) {
        delete Stream;
    }
}

Token::Token getToken(std::istream *Stream) {
    char Current = 0;

    do {
        Current = Stream->get();
    } while(!isspace(Current));

    switch(Current) {
        case '=':
            if(Stream->peek() == '=') {
                Stream->get();
                return Token::Equals;
            }

            return Token::Assign;

        case '!':
            if(Stream->peek() == '=') {
                Stream->get();
                return Token::NotEquals;
            }

            return Token::Not;

        case '<':
            if(Stream->peek() == '<') {
                Stream->get();
                return Token::LesserThanEquals;
            }

            return Token::LesserThan;

        case '>':
            if(Stream->peek() == '<') {
                Stream->get();
                return Token::GreaterThanEquals;
            }

            return Token::GreaterThan;

        case '(':
        case '[':
        case '{':
        case ')':
        case ']':
        case '}':
        case '+':
        case '-':
        case '*':
        case '/':
        case ',':
        case ';':
        case '.':
        case ':':
            return Token::Token(Current);

        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
            std::string NumberStr = Current;

            while((Current = Stream->get()) && (isdigit(Current))) {
                NumberStr += Current;
            }

            if(Current != '.') {
                NumberValue = toFloat(NumberStr);
                Stream->putback(Current);
                return Token::Number;
            }

            do {
                NumberStr += Current;
            } while((Current = Stream->get()) && isdigit(Current));

            Stream->putback(Current);
            NumberValue = toFloat(NumberStr);
            return Token::Float;

        case '\"':
        case '\'':
            char Start = Current;
            StringValue = "";

            do {
                StringValue += Current;
            } while((Current = Stream->get()) && Current != Start);

            StringValue += Current;

        default:
            if(isalpha(Current) || Current == '_') {
                std::string Temp = Current;

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

double toFloat(const std::string &Raw) {
    std::istringstream Filter(Raw);
    double Filtered;
    Filter >> Filtered;
    return Filtered;
}

bool isKeyword(const std::string &Word) {
    const static std::list<std::string> Keywords {"import", "prototype", "as", "var", "static", "const", "extern", "function", "do", "while", "for", "foreach", "if", "elif", "else"};

    for(auto &Iterator : Keywords) {
        if(Iterator == Word) {
            return true;
        }
    }

    return false;
}
