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
#include "syntax/AstPrinter.h"

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
    STMT_PRINT,
    EXEC,
    APPLY,
    NEWCLASS,
    NEWARRAY,
    PARENS,
    INDEXED,
    IDENT,
    TYPE_BASIC,
    TYPE_CLASS,
    TYPE_ARRAY,
    TYPE_APPLY,
    TYPE_PARAMETER,
    NILLCHK,
    EXPR_ASSIGN,
    EXPR_NEG,
    EXPR_NOT,
    EXPR_OR,
    EXPR_AND,
    EXPR_EQ,
    EXPR_NE,
    EXPR_LT,
    EXPR_GT,
    EXPR_LE,
    EXPR_GE,
    EXPR_ADD,
    EXPR_SUB,
    EXPR_MUL,
    EXPR_DIV,
    EXPR_MOD,
    CONSTANT,
    CALLEXPR,
    THISEXPR,
    READINTEXPR,
    READLINEEXPR,
    TYPE_NIL,

    /**
     * Tags for constant and TypeLiteral
     */
    TYPE_VOID,
    TYPE_INT,
    TYPE_BOOL,
    TYPE_STRING
} astKind ;

typedef enum __lvKind__ {
    LOCAL_VAR,
    PARAM_VAR,
    MEMBER_VAR,
    ARRAY_ELEMENT
} lvKind;


// forword defination
class Node;
class ClassDef;
class VarDef;
class Block;
class Expr;
class TypeLiteral;

// forword defination
class Visitor;

// forword defination(extern)
class Type;

// forword defination owing to circular reference
class Variable;
class Function;
class Class;

// forword defination owing to circular reference
class LocalScope;
class GlobalScope;

class Temp;

class Node {
    public:
        astKind kind;       ///< kind of node
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
};

class ClassDef:public Node {
    public:
        char *name;
        char *parent;
        List <Node *> *fields;
        Class *symbol;

        ClassDef(char *name, char *parent, List <Node *> *fields, yyltype *loc);
        virtual void accept(Visitor *v);
        virtual void print(AstPrinter *ap);
};

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
};

class VarDef:public Node {
    public:
        char *name;
        TypeLiteral *type;
        Variable *symbol;

        VarDef(char *name, TypeLiteral *type, yyltype *loc);
        virtual void accept(Visitor *v);
        virtual void print(AstPrinter *ap);
};

class Block:public Node {
    public:
        List <Node *> *block;
        LocalScope *associatedScope;

        Block(List <Node *> *block, yyltype *loc);
        virtual void accept(Visitor *v);
        virtual void print(AstPrinter *ap);
};

class WhileLoop:public Node {
    public:
        Expr *condition;
        Node *loopBody;

        WhileLoop(Expr *condition, Node *loopBody, yyltype *loc);
        virtual void accept(Visitor *v);
        virtual void print(AstPrinter *ap);
};

class ForLoop:public Node {
    public:
        Node *init;
        Expr *condition;
        Node *update;
        Node *loopBody;

        ForLoop(Node *init, Expr *condition, Node *update, Node *loopBody, yyltype *loc);
        virtual void accept(Visitor *v);
        virtual void print(AstPrinter *ap);
};

class If:public Node {
    public:
        Expr *condition;
        Node *trueBranch;
        Node *falseBranch;

        If(Expr *condition, Node *trueBranch, Node *falseBranch, yyltype *loc);
        virtual void accept(Visitor *v);
        virtual void print(AstPrinter *ap);
};

class Exec:public Node {
    public:
        Expr *expr;

        Exec(Expr *expr, yyltype *loc);
        virtual void accept(Visitor *v);
        virtual void print(AstPrinter *ap);
};

class Print:public Node {
    public:
        List <Expr *> *exprs;

        Print(List <Expr *> *exprs, yyltype *loc);
        virtual void accept(Visitor *v);
        virtual void print(AstPrinter *ap);
};

class Return:public Node {
    public:
        Expr *expr;

        Return(Expr *expr, yyltype *loc);
        virtual void accept(Visitor *v);
        virtual void print(AstPrinter *ap);
};

class Expr:public Node {
    public:
        Type *type;
        Temp *val;
        bool isClass;       ///< make all fields become private
        bool usedForRef;

        Expr(astKind kind, yyltype *loc);
};

class Apply:public Expr {
    public:
        Expr *receiver;
        char *method;
        List <Expr *> *actuals;
        Function *symbol;
        bool isArrayLength;

        Apply(Expr *receiver, char *method, List <Expr *> *actuals, yyltype *loc);
        virtual void accept(Visitor *v);
        virtual void print(AstPrinter *ap);
};

class NewClass:public Expr {
    public:
        char *className;
        Class *symbol;

        NewClass(char *className, yyltype *loc);
        virtual void accept(Visitor *v);
        virtual void print(AstPrinter *ap);
};

class NewArray:public Expr {
    public:
        TypeLiteral *elementType;
        Expr *length;

        NewArray(TypeLiteral *elementType, Expr *length, yyltype *loc);
        virtual void accept(Visitor *v);
        virtual void print(AstPrinter *ap);
};

class LValue:public Expr {
    public:
        lvKind kind;

        LValue(astKind kind, yyltype *loc);
};

class Assign:public Node {
    public:
        LValue *left;
        Expr *expr;

        Assign(LValue *left, Expr *expr, yyltype *loc);
        virtual void accept(Visitor *v);
        virtual void print(AstPrinter *ap);
};

class Unary:public Expr {
    public:
        Expr *expr;

        Unary(astKind kind, Expr *expr, yyltype *loc);
        virtual void accept(Visitor *v);
        virtual void print(AstPrinter *ap);
};

class Binary:public Expr {
    public:
        Expr *left;
        Expr *right;

        Binary(astKind kind, Expr *left, Expr *right, yyltype *loc);
        virtual void accept(Visitor *v);
        virtual void print(AstPrinter *ap);
};

class CallExpr:public Expr {
    public:
        Expr *receiver;
        char *method;
        List <Expr *> *actuals;
        Function *symbol;
        bool isArrayLength;

        CallExpr(Expr *receiver, char *method, List <Expr *> *actuals, yyltype *loc);
        virtual void accept(Visitor *v);
        virtual void print(AstPrinter *ap);
};

class ReadIntExpr:public Expr {
    public:
        ReadIntExpr(yyltype *loc);
        virtual void accept(Visitor *v);
        virtual void print(AstPrinter *ap);
};

class ReadLineExpr:public Expr {
    public:
        ReadLineExpr(yyltype *loc);
        virtual void accept(Visitor *v);
        virtual void print(AstPrinter *ap);
};

class ThisExpr:public Expr {
    public:
        ThisExpr(yyltype *loc);
        virtual void accept(Visitor *v);
        virtual void print(AstPrinter *ap);
};

class Indexed:public LValue {
    public:
        Expr *array;
        Expr *index;

        Indexed(Expr *array, Expr *index, yyltype *loc);
        virtual void accept(Visitor *v);
        virtual void print(AstPrinter *ap);
};

class Ident:public LValue {
    public:
        Expr *owner;
        char *name;
        Variable *symbol;
        bool isDefined;

        Ident(Expr *owner, char *name, yyltype *loc);
        virtual void accept(Visitor *v);
        virtual void print(AstPrinter *ap);
};

class Constant:public Expr {
    public:
        astKind typekind;
        int num_val;
        char *str_val;

        Constant(astKind typekind, int num_val, yyltype *loc);
        Constant(astKind typekind, char *str_val, yyltype *loc);
        virtual void accept(Visitor *v);
        virtual void print(AstPrinter *ap);
};

class Null:public Expr {
    public:
        Null(yyltype *loc);
        virtual void accept(Visitor *v);
        virtual void print(AstPrinter *ap);
};

class TypeLiteral:public Node {
    public:
        Type *type;

        TypeLiteral(astKind kind, yyltype *loc);
};

class TypeBasic:public TypeLiteral {
    public:
        astKind typekind;

        TypeBasic(astKind typekind, yyltype *loc);
        virtual void accept(Visitor *v);
        virtual void print(AstPrinter *ap);
};

class TypeClass:public TypeLiteral {
    public:
        char *name;

        TypeClass(char *name, yyltype *loc);
        virtual void accept(Visitor *v);
        virtual void print(AstPrinter *ap);
};

class TypeArray:public TypeLiteral {
    public:
        TypeLiteral *elementType;

        TypeArray(TypeLiteral *elementType, yyltype *loc);
        virtual void accept(Visitor *v);
        virtual void print(AstPrinter *ap);
};

class Visitor {
    public:
        /// \brief this function won't get invoked ever
        void visitNode(Node *that);

        // below functions will get invoked

        void visitProgram(Program *that);
        void visitClassDef(ClassDef *that);
        void visitFuncDef(FuncDef *that);
        void visitVarDef(VarDef *that);
        void visitBlock(Block *that);
        void visitWhileLoop(WhileLoop *that);
        void visitForLoop(ForLoop *that);
        void visitIf(If *that);
        void visitExec(Exec *that);
        void visitReturn(Return *that);
        void visitApply(Apply *that);
        void visitNewClass(NewClass *that);
        void visitNewArray(NewArray *that);
        void visitAssign(Assign *that);
        void visitUnary(Unary *that);
        void visitBinary(Binary *that);
        void visitCallExpr(CallExpr *that);
        void visitReadIntExpr(ReadIntExpr *that);
        void visitReadLineExpr(ReadLineExpr *that);
        void visitPrint(Print *that);
        void visitThisExpr(ThisExpr *that);
        void visitLValue(LValue *that);
        void visitIndexed(Indexed *that);
        void visitIdent(Ident *that);
        void visitConstant(Constant *that);
        void visitNull(Null *that);
        void visitTypeBasic(TypeBasic*that);
        void visitTypeClass(TypeClass *that);
        void visitTypeArray(TypeArray *that);
};



#endif
