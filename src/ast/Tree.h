/*!
 * \file Tree.h
 * \brief
 *
 * \author sabertazimi, <sabertazimi@gmail.com>
 * \version 1.0
 * \date 2016
 * \license MIT
 */

#ifndef TREE_H
#define TREE_H

#include <iostream>
#include <string>
#include "location.h"
#include "libs/List.h"
#include "ast/Type.h"
#include "semantic/Scope.h"
#include "semantic/Symbol.h"
#include "ir/Tac.h"

class Visitor;

typedef enum __ast_kind__ {
    FIELD_VAR = 1,
    FIELD_FUNC
    EXPR_BOOL = 41,
    EXPR_ASSIGN,
    EXPR_OR,
    EXPR_AND,
    EXPR_EQ,
    EXPR_EQ = 81,
    EXPR_NE
    EXPR_LT = 91,
    EXPR_GT,
    EXPR_LE,
    EXPR_GE
    EXPR_ADD = 101,
    EXPR_SUB
    EXPR_MUL = 111,
    EXPR_DIV,
    EXPR_MOD
    EXPR_PLUS = 121,
    EXPR_MINUS,
    EXPR_NOT
    EXPR_THIS = 131,
    EXPR_INDEX,
    EXPR_CLASS_FIELD,
    EXPR_CLASS_CALL,
    EXPR_FUNC_CALL,
    EXPR_IDENT = 141,
    EXPR_CONST,
    EXPR_READINT,
    EXPR_READLINE,
    EXPR_NEWCLASS,
    EXPR_NEWARRAY
    STMT_VAR_DEF = 31,
    STMT_EXPR,
    STMT_IF,
    STMT_WHILE,
    STMT_FOR,
    STMT_RETURN,
    STMT_PRINT
    CONST_INT = 1,
    CONST_BOOL,
    CONST_STRING,
    CONST_NIL
} ast_kind ;

class Node {
    public:
        ast_kind kind;      ///< kind of node
        yyltype* loc;       ///< location information
        Type* type;         ///< type information

        /// \brief type check function
        /// \return bool
        virtual bool isClass(void);

        /// \brief type check function
        /// \return bool
        virtual bool isFunc(void);

        /// \brief type check function
        /// \return bool
        virtual bool isVar(void);

        /// \brief type check function
        /// \return bool
        virtual bool isStmt(void);

        /// \brief type check function
        /// \return bool
        virtual bool isExpr(void);

        /// \brief type check function
        /// \return bool
        virtual bool isType(void);

        /// \brief type check function
        /// \return bool
        virtual bool isConst(void);

        /// \brief setup visitor
        public void accept(Visitor v);

        /// \brief generate information of node
        /// \return information string
        virtual string toString(void);
};



class Program:public Node {
    public:
        List < ClassDef > classes;
        Class main;
        GlobalScope globalScope;

        Program(List < ClassDef > classes, yyltype *loc);
        void accept(Visitor v);

        void printTo(IndentPrintWriter pw);
}

class ClassDef:public Node {
    public:
        String name;
        String parent;
        List < Node > fields;
        Class symbol;

        ClassDef(String name, String parent, List < Node > fields,
                yyltype *loc);
        void accept(Visitor v);

        void printTo(IndentPrintWriter pw);
}

class FuncDef:public Node {
    public:
        boolean statik;
        String name;
        TypeLiteral returnType;
        List < VarDef > formals;
        Block body;
        Function symbol;

        FuncDef(boolean statik, String name, TypeLiteral returnType,
                List < VarDef > formals, Block body, yyltype *loc);
        void accept(Visitor v);

        void printTo(IndentPrintWriter pw);
}

class VarDef:public Node {
    public:
        String name;
        TypeLiteral type;
        Variable symbol;

        VarDef(String name, TypeLiteral type, yyltype *loc);
        void accept(Visitor v);

        void printTo(IndentPrintWriter pw);
}

class Block:public Node {
    public:
        List < Node > block;
        LocalScope associatedScope;

        Block(List < Node > block, yyltype *loc);
        void accept(Visitor v);

        void printTo(IndentPrintWriter pw);
}

class WhileLoop:public Node {
    public:
        Expr condition;
        Node loopBody;

        WhileLoop(Expr condition, Node loopBody, yyltype *loc);
        void accept(Visitor v);

        void printTo(IndentPrintWriter pw);
}

class ForLoop:public Node {
    public:
        Node init;
        Expr condition;
        Node update;
        Node loopBody;

        ForLoop(Node init, Expr condition, Node update,
                Node loopBody, yyltype *loc);
        void accept(Visitor v);

        void printTo(IndentPrintWriter pw);
}

class If:public Node {
    public:
        Expr condition;
        Node trueBranch;
        Node falseBranch;

        If(Expr condition, Node trueBranch, Node falseBranch, yyltype *loc);
        void accept(Visitor v);

        void printTo(IndentPrintWriter pw);
}

class Exec:public Node {
    public:
        Expr expr;

        Exec(Expr expr, yyltype *loc);
        void accept(Visitor v);

        void printTo(IndentPrintWriter pw);
}

class Break:public Node {
    public:
        Break(yyltype *loc);
        void accept(Visitor v);

        void printTo(IndentPrintWriter pw);
}

class Print:public Node {
    public:
        List < Expr > exprs;

        Print(List < Expr > exprs, yyltype *loc);
        void accept(Visitor v);

        void printTo(IndentPrintWriter pw);
}

class Return:public Node {
    public:
        Expr expr;

        Return(Expr expr, yyltype *loc);
        void accept(Visitor v);

        void printTo(IndentPrintWriter pw);
}

class Expr:public Node {
    public:
        Type type;
        Temp val;
        boolean isClass;
        boolean usedForRef;

        Expr(int tag, yyltype *loc);
}

class Apply:public Expr {
    public:
        Expr receiver;
        String method;
        List < Expr > actuals;
        Function symbol;
        boolean isArrayLength;

        Apply(Expr receiver, String method, List < Expr > actuals,
                yyltype *loc);
        void accept(Visitor v);

        void printTo(IndentPrintWriter pw);
}

class NewClass:public Expr {
    public:
        String className;
        Class symbol;

        NewClass(String className, yyltype *loc);
        void accept(Visitor v);

        void printTo(IndentPrintWriter pw);
}

class NewArray:public Expr {
    public:
        TypeLiteral elementType;
        Expr length;

        NewArray(TypeLiteral elementType, Expr length, yyltype *loc);
        void accept(Visitor v);

        void printTo(IndentPrintWriter pw);
}

typedef enum _lvKind_ {
    LOCAL_VAR,
    PARAM_VAR,
    MEMBER_VAR,
    ARRAY_ELEMENT
} lvKind;

class LValue:public Expr {
    public:

        LValue(int tag, yyltype *loc);
}

class Assign:public Node {
    public:
        LValue left;
        Expr expr;

        Assign(LValue left, Expr expr, yyltype *loc);
        void accept(Visitor v);

        void printTo(IndentPrintWriter pw);
}

class Unary:public Expr {
    public:
        Expr expr;

        Unary(int kind, Expr expr, yyltype *loc);
        void unaryOperatorToString(IndentPrintWriter pw, String op);

        void accept(Visitor v);

        void printTo(IndentPrintWriter pw);
}

class Binary:public Expr {
    public:
        Expr left;
        Expr right;

        Binary(int kind, Expr left, Expr right, yyltype *loc);
        private void binaryOperatorPrintTo(IndentPrintWriter pw, String op);

        void accept(Visitor visitor);

        void printTo(IndentPrintWriter pw);
}

class CallExpr:public Expr {
    public:
        Expr receiver;

        String method;

        List < Expr > actuals;

        Function symbol;

        boolean isArrayLength;

        CallExpr(Expr receiver, String method, List < Expr > actuals,
                yyltype *loc);
        void accept(Visitor visitor);

        void printTo(IndentPrintWriter pw);
}

class ReadIntExpr:public Expr {
    public:
        ReadIntExpr(yyltype *loc);
        void accept(Visitor visitor);

        void printTo(IndentPrintWriter pw);
}

class ReadLineExpr:public Expr {
    public:
        ReadLineExpr(yyltype *loc);
        void accept(Visitor visitor);

        void printTo(IndentPrintWriter pw);
}

class ThisExpr:public Expr {
    public:
        ThisExpr(yyltype *loc);
        void accept(Visitor visitor);

        void printTo(IndentPrintWriter pw);
}

class Indexed:public LValue {
    public:
        Expr array;
        Expr index;

        Indexed(Expr array, Expr index, yyltype *loc);
        void accept(Visitor v);

        void printTo(IndentPrintWriter pw);
}

class Ident:public LValue {
    public:
        Expr owner;
        String name;
        Variable symbol;
        boolean isDefined;

        Ident(Expr owner, String name, yyltype *loc);
        void accept(Visitor v);

        void printTo(IndentPrintWriter pw);
}

class Literal:public Expr {
    public:
        int typeTag;
        Object value;

        Literal(int typeTag, Object value, yyltype *loc);
        void accept(Visitor v);

        void printTo(IndentPrintWriter pw);
}

class Null:public Expr {
    public:
        Null(yyltype *loc);
        void accept(Visitor v);

        void printTo(IndentPrintWriter pw);
}

class TypeLiteral:public Node {
    public:
        Type type;

        TypeLiteral(int tag, yyltype *loc);
}

class TypeIdent:public TypeLiteral {
    public:
        int typeTag;

        TypeIdent(int typeTag, yyltype *loc);
        void accept(Visitor v);

        void printTo(IndentPrintWriter pw);
}

class TypeClass:public TypeLiteral {
    public:
        String name;

        TypeClass(String name, yyltype *loc);
        void accept(Visitor visitor);

        void printTo(IndentPrintWriter pw);
}

class TypeArray:public TypeLiteral {
    public:
        TypeLiteral elementType;

        TypeArray(TypeLiteral elementType, yyltype *loc);
        void accept(Visitor v);

        void printTo(IndentPrintWriter pw);
}

#endif
