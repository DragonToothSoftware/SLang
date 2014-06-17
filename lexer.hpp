#ifndef _ROOT_LEXER_HPP
#define _ROOT_LEXER_HPP

#include <string>

namespace SLangLexer {
    namespace Token {
        enum {
            END      = -1,
            FUNCTION = -2, EXTERN = -3,
            NUMBER   = -4, IDENTIFIER = -5,
        };
    }

    class SLangLexer {
        private:
            std::string NameValue    = "",
                        Buffer       = "";
                 double NumberValue  = 0;

            int get       ();
                SLangLexer(SLangLexer&);

        public:
                SLangLexer(const std::string&);

                 int    getToken      ();
            std::string getNameValue  ();
                 double getNumberValue();
    };
}

namespace lex = SLangLexer;
namespace Token = lex::Token;

#endif
