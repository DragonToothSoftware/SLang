#include <parser.hpp>

namespace SLangParser {
    SLangParser::SLangParser(SLangParser&) {}

    ast::Expr* SLangParser::Error(std::string &Message) {
    }

    ast::Expr* SLangParser::ErrorP(std::string &Message) {
    }

    SLangParser::SLangParser() {}

    int SLangParser::next() {
    }

    int SLangParser::getTokenPrecedence() {
    }

    ast::Expr* parseExpr() {
    }





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

static int getNextToken() {
  return CurTok = gettok();
}

static int GetTokPrecedence() {
  if (!isascii(CurTok))
    return -1;
  
  int TokPrec = BinopPrecedence[CurTok];
  if (TokPrec <= 0) return -1;
  return TokPrec;
}

ExprAST *Error(const char *Str) { fprintf(stderr, "Error: %s\n", Str);return 0;}
PrototypeAST *ErrorP(const char *Str) { Error(Str); return 0; }

static ExprAST *ParseIdentifierExpr() {
  std::string IdName = IdentifierStr;
  
  getNextToken();  // eat identifier.
  
  if (CurTok != '(') // Simple variable ref.
    return new VariableExprAST(IdName);
  
  // Call.
  getNextToken();  // eat (
  std::vector<ExprAST*> Args;
  if (CurTok != ')') {
    while (1) {
      ExprAST *Arg = ParseExpression();
      if (!Arg) return 0;
      Args.push_back(Arg);

      if (CurTok == ')') break;

      if (CurTok != ',')
        return Error("Expected ')' or ',' in argument list");
      getNextToken();
    }
  }

  // Eat the ')'.
  getNextToken();
  
  return new CallExprAST(IdName, Args);
}


static ExprAST *ParseNumberExpr() {
  ExprAST *Result = new NumberExprAST(NumVal);
  getNextToken(); // consume the number
  return Result;
}

static ExprAST *ParseParenExpr() {
  getNextToken();  // eat (.
  ExprAST *V = ParseExpression();
  if (!V) return 0;
  
  if (CurTok != ')')
    return Error("expected ')'");
  getNextToken();  // eat ).
  return V;
}

static ExprAST *ParsePrimary() {
  switch (CurTok) {
  default: return Error("unknown token when expecting an expression");
  case tok_identifier: return ParseIdentifierExpr();
  case tok_number:     return ParseNumberExpr();
  case '(':            return ParseParenExpr();
  }
}

static ExprAST *ParseBinOpRHS(int ExprPrec, ExprAST *LHS) {
  while (1) {
    int TokPrec = GetTokPrecedence();
    
    if (TokPrec < ExprPrec)
      return LHS;
    
    int BinOp = CurTok;
    getNextToken();  // eat binop
    
    // Parse the primary expression after the binary operator.
    ExprAST *RHS = ParsePrimary();
    if (!RHS) return 0;
    
    // If BinOp binds less tightly with RHS than the operator after RHS, let
    // the pending operator take RHS as its LHS.
    int NextPrec = GetTokPrecedence();
    if (TokPrec < NextPrec) {
      RHS = ParseBinOpRHS(TokPrec+1, RHS);
      if (RHS == 0) return 0;
    }
    
    // Merge LHS/RHS.
    LHS = new BinaryExprAST(BinOp, LHS, RHS);
  }
}

static ExprAST *ParseExpression() {
  ExprAST *LHS = ParsePrimary();
  if (!LHS) return 0;
  
  return ParseBinOpRHS(0, LHS);
}

static PrototypeAST *ParsePrototype() {
  if (CurTok != tok_identifier)
    return ErrorP("Expected function name in prototype");

  std::string FnName = IdentifierStr;
  getNextToken();
  
  if (CurTok != '(')
    return ErrorP("Expected '(' in prototype");
  
  std::vector<std::string> ArgNames;
  while (getNextToken() == tok_identifier)
    ArgNames.push_back(IdentifierStr);
  if (CurTok != ')')
    return ErrorP("Expected ')' in prototype");
  
  // success.
  getNextToken();  // eat ')'.
  
  return new PrototypeAST(FnName, ArgNames);
}

/// definition ::= 'def' prototype expression
static FunctionAST *ParseDefinition() {
  getNextToken();  // eat def.
  PrototypeAST *Proto = ParsePrototype();
  if (Proto == 0) return 0;

  if (ExprAST *E = ParseExpression())
    return new FunctionAST(Proto, E);
  return 0;
}

/// toplevelexpr ::= expression
static FunctionAST *ParseTopLevelExpr() {
  if (ExprAST *E = ParseExpression()) {
    // Make an anonymous proto.
    PrototypeAST *Proto = new PrototypeAST("", std::vector<std::string>());
    return new FunctionAST(Proto, E);
  }
  return 0;
}

/// external ::= 'extern' prototype
static PrototypeAST *ParseExtern() {
  getNextToken();  // eat extern.
  return ParsePrototype();
}
