/*!
 * \file Tree.h
 * \brief
 *
 * \author sabertazimi, <sabertazimi@gmail.com>
 * \version 1.0
 * \date 2016
 * \license MIT
 */

#ifndef SYNTAX_TREE_H
#define SYNTAX_TREE_H

#include <iostream>
#include "location.h"
#include "libs/List.h"
#include "syntax/Type.h"
#include "syntax/AstPrinter.h"
#include "semantic/Scope.h"
#include "semantic/Symbol.h"
#include "ir/Tac.h"

class Visitor;

typedef enum __astKind__ {
    PROGRAM,
    CLASS_DEF,
    FUNC_DEF,
    VAR_DEF,
    STMT_BLOCK,
    STMT_IF,
    STMT_WHILE,
    STMT_FOR,
    STMT_RETURN,
    STMT_PRINT
    EXEC,
    APPLY,
    NEWCLASS,
    NEWARRAY,
    PARENS,
    INDEXED,
    IDENT,
    CONSTANT,
    TYPE_BASIC,
    TYPE_CLASS,
    TYPE_ARRAY,
    TYPE_APPLY,
    TYPE_PARAMETER,
    NILLCHK,
    EXPR_ASSIGN,
    EXPR_NEG,
    EXPR_NOT
    EXPR_OR,
    EXPR_AND,
    EXPR_EQ,
    EXPR_NE
    EXPR_LT,
    EXPR_GT,
    EXPR_LE,
    EXPR_GE
    EXPR_ADD,
    EXPR_SUB
    EXPR_MUL,
    EXPR_DIV,
    EXPR_MOD
    EXPR_PLUS,
    CONSTANT
    CALLEXPR,
    THISEXPR,
    READINTEXPR,
    READLINEEXPR,
    NIL,

    /**
     * Tags for constant and TypeLiteral
     */
    TYPE_VOID,
    TYPE_INT,
    TYPE_BOOL,
    TYPE_STRING,

} astKind ;

typedef enum __lvKind__ {
    LOCAL_VAR,
    PARAM_VAR,
    MEMBER_VAR,
    ARRAY_ELEMENT
} lvKind;

class Node {
    public:
        astKind kind;      ///< kind of node
        yyltype* loc;       ///< location information
        Type* type;         ///< type information

        /// \brief constructor
        Node(astKind kind, yyltype *loc);

        /// \brief setup visitor
        virtual void accept(Visitor *v);

        /// \brief generate information of node
        /// \return information string
        virtual void print(AstPrinter *ap);
};



class Program:public Node {
    public:
        List <ClassDef *> *classes;
        Class *main;
        GlobalScope *globalScope;

        Program(List <ClassDef *> *classes, yyltype *loc);
        virtual void accept(Visitor *v);
        virtual void print(AstPrinter *ap);
}

class ClassDef:public Node {
    public:
        char *name;
        char *parent;
        List <Node *> *fields;
        Class *symbol;

        ClassDef(char *name, char *parent, List <Node *> *fields, yyltype *loc);
        virtual void accept(Visitor *v);
        virtual void print(AstPrinter *ap);
}

class FuncDef:public Node {
    public:
        char *name;
        TypeLiteral *returnType;
        List <VarDef *> *formals;
        Block *body;
        Function *symbol;

        FuncDef(char *name, TypeLiteral *returnType, List <VarDef *> *formals, Block *body, yyltype *loc);
        virtual void accept(Visitor *v);
        virtual void print(AstPrinter *ap);
}

class VarDef:public Node {
    public:
        char *name;
        TypeLiteral *type;
        Variable *symbol;

        VarDef(char *name, TypeLiteral *type, yyltype *loc);
        virtual void accept(Visitor *v);
        virtual void print(AstPrinter *ap);
}

class Block:public Node {
    public:
        List <Node *> *block;
        LocalScope *associatedScope;

        Block(List <Node *> *block, yyltype *loc);
        virtual void accept(Visitor *v);
        virtual void print(AstPrinter *ap);
}

class WhileLoop:public Node {
    public:
        Expr *condition;
        Node *loopBody;

        WhileLoop(Expr *condition, Node *loopBody, yyltype *loc);
        virtual void accept(Visitor *v);
        virtual void print(AstPrinter *ap);
}

class ForLoop:public Node {
    public:
        Node *init;
        Expr *condition;
        Node *update;
        Node *loopBody;

        ForLoop(Node *init, Expr *condition, Node *update, Node *loopBody, yyltype *loc);
        virtual void accept(Visitor *v);
        virtual void print(AstPrinter *ap);
}

class If:public Node {
    public:
        Expr *condition;
        Node *trueBranch;
        Node *falseBranch;

        If(Expr *condition, Node *trueBranch, Node *falseBranch, yyltype *loc);
        virtual void accept(Visitor *v);
        virtual void print(AstPrinter *ap);
}

class Exec:public Node {
    public:
        Expr *expr;

        Exec(Expr *expr, yyltype *loc);
        virtual void accept(Visitor *v);
        virtual void print(AstPrinter *ap);
}

class Print:public Node {
    public:
        List <Expr *> exprs;

        Print(List <Expr *> *exprs, yyltype *loc);
        virtual void accept(Visitor *v);
        virtual void print(AstPrinter *ap);
}

class Return:public Node {
    public:
        Expr *expr;

        Return(Expr *expr, yyltype *loc);
        virtual void accept(Visitor *v);
        virtual void print(AstPrinter *ap);
}

class Expr:public Node {
    public:
        Type type;
        Temp val;
        boolean isClass;
        boolean usedForRef;

        Expr(int kind, yyltype *loc);
}

class Apply:public Expr {
    public:
        Expr *receiver;
        char *method;
        List <Expr *> *actuals;
        Function *symbol;
        boolean isArrayLength;

        Apply(Expr *receiver, char *method, List <Expr *> *actuals, yyltype *loc);
        virtual void accept(Visitor *v);
        virtual void print(AstPrinter *ap);
}

class NewClass:public Expr {
    public:
        char *className;
        Class symbol;

        NewClass(char *className, yyltype *loc);
        virtual void accept(Visitor *v);
        virtual void print(AstPrinter *ap);
}

class NewArray:public Expr {
    public:
        TypeLiteral *elementType;
        Expr *length;

        NewArray(TypeLiteral *elementType, Expr *length, yyltype *loc);
        virtual void accept(Visitor *v);
        virtual void print(AstPrinter *ap);
}

class LValue:public Expr {
    public:
        lvKind kind;

        LValue(astKind kind, yyltype *loc);
}

class Assign:public Node {
    public:
        LValue left;
        Expr *expr;

        Assign(LValue left, Expr *expr, yyltype *loc);
        virtual void accept(Visitor *v);
        virtual void print(AstPrinter *ap);
}

class Unary:public Expr {
    public:
        Expr *expr;

        Unary(astKind kind, Expr *expr, yyltype *loc);
        virtual void accept(Visitor *v);
        virtual void print(AstPrinter *ap);
}

class Binary:public Expr {
    public:
        Expr *left;
        Expr *right;

        Binary(int kind, Expr *left, Expr *right, yyltype *loc);
        virtual void accept(Visitor *v);
        virtual void print(AstPrinter *ap);
}

class CallExpr:public Expr {
    public:
        Expr *receiver;
        char *method;
        List <Expr *> *actuals;
        Function *symbol;
        boolean isArrayLength;

        CallExpr(Expr *receiver, char *method, List <Expr *> *actuals, yyltype *loc);
        virtual void accept(Visitor *v);
        virtual void print(AstPrinter *ap);
}

class ReadIntExpr:public Expr {
    public:
        ReadIntExpr(yyltype *loc);
        virtual void accept(Visitor *v);
        virtual void print(AstPrinter *ap);
}

class ReadLineExpr:public Expr {
    public:
        ReadLineExpr(yyltype *loc);
        virtual void accept(Visitor *v);
        virtual void print(AstPrinter *ap);
}

class ThisExpr:public Expr {
    public:
        ThisExpr(yyltype *loc);
        virtual void accept(Visitor *v);
        virtual void print(AstPrinter *ap);
}

class Indexed:public LValue {
    public:
        Expr *array;
        Expr *index;

        Indexed(Expr *array, Expr *index, yyltype *loc);
        virtual void accept(Visitor *v);
        virtual void print(AstPrinter *ap);
}

class Ident:public LValue {
    public:
        Expr *owner;
        char *name;
        Variable *symbol;
        boolean isDefined;

        Ident(Expr *owner, char *name, yyltype *loc);
        virtual void accept(Visitor *v);
        virtual void print(AstPrinter *ap);
}

class Constant:public Expr {
    public:
        astKind typekind;
        int num_val;
        char *str_val;

        Constant(astKind typekind, int num_val, yyltype *loc);
        Constant(astKind typekind, char *str_val, yyltype *loc);
        virtual void accept(Visitor *v);
        virtual void print(AstPrinter *ap);
}

class Null:public Expr {
    public:
        Null(yyltype *loc);
        virtual void accept(Visitor *v);
        virtual void print(AstPrinter *ap);
}

class TypeLiteral:public Node {
    public:
        Type type;

        TypeLiteral(astKind kind, yyltype *loc);
}

class TypeBasic:public TypeLiteral {
    public:
        astKind typekind;

        TypeBasic(astKind typekind, yyltype *loc);
        virtual void accept(Visitor *v);
        virtual void print(AstPrinter *ap);
}

class TypeClass:public TypeLiteral {
    public:
        char *name;

        TypeClass(char *name, yyltype *loc);
        virtual void accept(Visitor *v);
        virtual void print(AstPrinter *ap);
}

class TypeArray:public TypeLiteral {
    public:
        TypeLiteral *elementType;

        TypeArray(TypeLiteral *elementType, yyltype *loc);
        virtual void accept(Visitor *v);
        virtual void print(AstPrinter *ap);
}

#endif
