#ifndef _ROOT_AST_HPP
#define _ROOT_AST_HPP

#include <string>
#include <vector>

namespace AbstractSyntaxTree {
    class Expr {
        public:
            virtual ~Expr();
    };

    class NumberExpr : Expr {
        public:
            NumberExpr(double val) {}
    };

    class VariableExpr : Expr {
        private:
            std::string Name;

        public:
            VariableExpr(const std::string &name) : Name(name) {}
    };

    class BinaryExpr : Expr {
        public:
            BinaryExpr(char op, Expr *lhs, Expr *rhs) {}
    };

    class CallExpr : Expr {
        private:
            std::string        Callee;
            std::vector<Expr*> Args;

        public:
            CallExpr(const std::string &callee, std::vector<Expr*> &args)
                : Callee(callee), Args(args) {}
    };

    class Prototype {
        private:
            std::string              Name;
            std::vector<std::string> Args;
 
        public:
            Prototype(const std::string &name, const std::vector<std::string> &args)
                : Name(name), Args(args) {}
    };

    class Function {
        public:
            Function(Prototype *proto, Expr *body) {}
    };
}

namespace AST = AbstractSyntaxTree;

#endif
