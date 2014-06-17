#ifndef _ROOT_PARSER_HPP
#define _ROOT_PARSER_HPP

#include <ast.hpp>

#include <string>
#include    <map>

namespace SLangParser {
    class SLangParser {
        private:
                 int            Current;
            std::map<char, int> BinopPrecedence;

            SLangParser(SLangParser&);

            ast::Expr*      Error (const std::string&);
            ast::Prototype* ErrorP(const std::string&);

        public:
            SLangParser();

            int next              ();
            int getTokenPrecedence();

            ast::Expr*      parseExpr        ();
            ast::Expr*      parseNameExpr    ();
            ast::Expr*      parseNumberExpr  ();
            ast::Expr*      parseParenExpr   ();
            ast::Expr*      parsePrimary     ();
            ast::Expr*      parseBinOpRHS    (int=0, Expr*);
            ast::Expr*      parseExpression  ();
            ast::Prototype* parsePrototype   ();
            ast::Function*  parseFunction    ();
            ast::Function*  parseTopLevelExpr();
            ast::Prototype* parseExtern      ();
    }

    typedef SLangParser parse;
}

namespace parse = SLangParser;

#endif
