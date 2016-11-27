/*!
 * \file Visitor.h
 * \brief
 *
 * \author sabertazimi, <sabertazimi@gmail.com>
 * \version 1.0
 * \date 2016
 * \license MIT
 */

#ifndef AST_VISITOR_H
#define AST_VISITOR_H

class Visitor {
    public:
        // brief visit functions

        /// \brief this function won't get invoked ever
        void visitNode(Node that);

        // below functions will get invoked

        void visitProgram(Program that);
        void visitClassDef(ClassDef that);
        void visitMethodDef(FuncDef that);
        void visitVarDef(VarDef that);
        void visitBlock(Block that);
        void visitWhileLoop(WhileLoop that);
        void visitForLoop(ForLoop that);
        void visitIf(If that);
        void visitExec(Exec that);
        void visitBreak(Break that);
        void visitReturn(Return that);
        void visitApply(Apply that);
        void visitNewClass(NewClass that);
        void visitNewArray(NewArray that);
        void visitAssign(Assign that);
        void visitUnary(Unary that);
        void visitBinary(Binary that);
        void visitCallExpr(CallExpr that);
        void visitReadIntExpr(ReadIntExpr that);
        void visitReadLineExpr(ReadLineExpr that);
        void visitPrint(Print that);
        void visitThisExpr(ThisExpr that);
        void visitLValue(LValue that);
        void visitIndexed(Indexed that);
        void visitIdent(Ident that);
        void visitLiteral(Literal that);
        void visitNull(Null that);
        void visitTypeIdent(TypeIdent that);
        void visitTypeClass(TypeClass that);
        void visitTypeArray(TypeArray that);
}

#endif				/* !AST_VISITOR_H */
