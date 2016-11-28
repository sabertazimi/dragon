/*!
 * \file Visitor.h
 * \brief
 *
 * \author sabertazimi, <sabertazimi@gmail.com>
 * \version 1.0
 * \date 2016
 * \license MIT
 */

#ifndef SYNTAX_VISITOR_H
#define SYNTAX_VISITOR_H

class Visitor {
    public:
        // brief visit functions

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
}

#endif				/* !SYNTAX_VISITOR_H */