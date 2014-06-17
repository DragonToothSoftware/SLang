#include <lexer.hpp>
#include  <util.hpp>

#include <sstream>

#include <cctype>

namespace SLangLexer {
    int SLangLexer::get() {
        static std::istringstream Stream(Buffer);

        return (Stream.peek() ? Stream.get() : 0);
    }

    SLangLexer::SLangLexer(SLangLexer &Copy) {}

    SLangLexer::SLangLexer(const std::string &buffer)
        : Buffer(buffer) {}

    int SLangLexer::getToken() {
        static int Previous = 0;

        do {
            Previous = this->get();
        } while(isspace(Previous));

        if(isalpha(Previous)) {
            do {
                this->NameValue += Previous;
            } while(isalnum(Previous = this->get()));

            if(NameValue == "function") {
                return Token::FUNCTION;
            }

            else if(NameValue == "extern") {
                return Token::EXTERN;
            }

            return Token::IDENTIFIER;
        }

        else if((isdigit(Previous)) || (Previous == '.')) {
            std::string Number;

            do {
                Number += Previous;
                Previous = this->get();
            } while((isdigit(Previous)) || (Previous == '.'));

            this->NumberValue = util::toFloat(Number);
            return Token::NUMBER;
        }

        else if(Previous == '#') {
            do {
                Previous = this->get();
            } while((Previous != '\n') || (Previous != '\r'));

            if(Previous != 0) {
                return this->getToken();
            }

            else if(Previous == 0) {
                return Token::END;
            }
        }

        int Cached = Previous;
        Previous = this->get();
        return Cached;
    }

    std::string SLangLexer::getNameValue() {
        return this->NameValue;
    }

    double SLangLexer::getNumberValue() {
        return this->NumberValue;
    }
}
