#include <lexer.hpp>

#include    <vector>
#include    <cctype>

#include <util.hpp>

namespace LexicalAnalyzer {
    char LexicalAnalyzer::getChar() {
        char Current = this->Stream.get();

        if(Current == '\n' || Current == '\r') {
            this->LineColumn = 0;
            this->LineNumber++;
        }

        else {
            this->LineColumn++;
        }

        return Current;
    }

    void LexicalAnalyzer::putBack(char Current) {
        --LineColumn != 0 ? this->Stream.putback(Current) : this->Stream.putback(Current), this->LineNumber--;
    }

    void LexicalAnalyzer::set(std::istream &&stream) {
        this->Stream = stream;
    }

    Token::Lexeme LexicalAnalyzer::getLexeme() {
        static char Current = 0;

        do {
            Current = this->getChar();
        } while(isspace(Current));

        switch(Current) {
            case '=': return (this->Stream.peek() == '=' ? this->getChar(), this->CachedValue = Token::Equals            : this->CachedValue = Token::Assign);
            case '!': return (this->Stream.peek() == '=' ? this->getChar(), this->CachedValue = Token::NotEquals         : this->CachedValue = Token::Not);
            case '<': return (this->Stream.peek() == '=' ? this->getChar(), this->CachedValue = Token::LesserThanEquals  : this->CachedValue = Token::LesserThan);
            case '>': return (this->Stream.peek() == '=' ? this->getChar(), this->CachedValue = Token::GreaterThanEquals : this->CachedValue = Token::GreaterThan);

            case '(': case '[': case '{': case ')':
            case ']': case '}': case '+': case '-':
            case '*': case '/': case ',': case ';':
            case ':': case '.':
                return this->CachedValue = Token::Lexeme(Current);

            case '0' ... '9': {
                std::string NumberStr;

                do {
                    NumberStr += Current;
                } while(((Current = this->getChar()) == '.') || (isdigit(Current)));

                this->putBack(Current);
                this->NumberValue = stod(NumberStr);
                return this->CachedValue = Token::Number;
            }

            case '\"': case '\'': {
                char Start = Current;
                StringValue = "";

                do {
                    StringValue += Current;
                } while((Current = this->getChar()) && Current != Start);

                this->StringValue += Current;
                return this->CachedValue = Token::String;
            }

            default: {
                if(isalpha(Current) || Current == '_') {
                    std::string Temp (1, Current);

                    while((Current = this->getChar()) && (isalnum(Current) || Current == '_')) {
                        Temp += Current;
                    }

                    this->putBack(Current);

                    if(Temp == "True" || Temp == "False") {
                        this->BoolValue = Temp;
                        return this->CachedValue = Token::Boolean;
                    }

                    else if(util::isKeyword(Temp)) {
                        this->KeywordValue = Temp;
                        return this->CachedValue = Token::Keyword;
                    }

                    this->NameValue = Temp;
                    return this->CachedValue = Token::Name;
                }
            }
        }
    }

    std::string LexicalAnalyzer::getName() const {
        return this->NameValue;
    }

    std::string LexicalAnalyzer::getKeyword() const {
        return this->KeywordValue;
    }

    std::string LexicalAnalyzer::getString() const {
        return this->StringValue;
    }

    std::string LexicalAnalyzer::getBool() const {
        return this->BoolValue;
    }

    double LexicalAnalyzer::getNumber() const {
        return this->NumberValue;
    }

    std::tuple<int, int> LexicalAnalyzer::getLocation() const {
        return std::make_tuple(this->LineNumber, this->LineColumn);
    }

    Token::Lexeme LexicalAnalyzer::flushCache() const {
        return this->CachedValue;
    }

    LexicalAnalyzer::operator bool() const {
        return this->Stream.good();
    }
}

std::ostream& operator<<(std::ostream& Out, const LexicalAnalyzer::LexicalAnalyzer &Lexer) {
    static bool Shown = false;

    if(!Shown) {
        Out<<"(Token Type, Token Name, Line Number, Line Column)\n"
           <<"--------------------------------------------------\n";
        Shown = true;
    }

    Out<<"("<< Lexer.flushCache() <<", "<< Lexer.getName() <<", "<< std::get<0>(Lexer.getLocation()) <<", "<< std::get<1>(Lexer.getLocation()) <<")";
}
