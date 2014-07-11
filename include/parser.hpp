#ifndef _ROOT_INCLUDE_PARSER_HPP
#define _ROOT_INCLUDE_PARSER_HPP

#include <string>
#include <vector>

#include <lexer.hpp>
#include  <util.hpp>

namespace AbstractSyntaxTree {
    class Expression {
        public:
            virtual ~Expression() {}
    };

    class NumberExpression : public Expression {
        private:
            double Value;

        public:
            NumberExpression(double value)
                : Value(value) {}
    };

    class VariableExpression : public Expression {
        private:
            std::string Name;

        public:
            VariableExpression(const std::string &name)
                : Name(name) {}
    };


    class BinaryExpression : public Expression {
        private:
            char     Operator;
            ExprAST *LeftHandSide,
                    *RightHandSide;

        public:
            BinaryExpression(char op, Expression *lhs, Expression *rhs)
                : Operator(op), LeftHandSide(lhs), RightHandSide(rhs) {}
    };

    class CallExpression : public Expression {
        private:
            std::string              Callee;
            std::vector<Expression*> Args;

        public:
            CallExpression(const std::string &callee, std::vector<Expression*> &args)
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
        private:
            PrototypeAST *Prototype;
            Expression   *Body;

        public:
            Function(Prototype *prototype, Expression *body)
                : Prototype(prototype), Body(body) {}
    };
}

#endif
