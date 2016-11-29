/*
 * semantic.h
 * Copyright (C) 2016 sabertazimi <sabertazimi@gmail.com>
 *
 * Distributed under terms of the MIT license.
 */

#ifndef SEMANTIC_H
#define SEMANTIC_H

#include <string>
#include <map>
#include "syntax/Tree.h"
#include "syntax/Type.h"
#include "semantic/Scope.h"
#include "semantic/Symbol.h"
#include "errors/errors.h"

using namespace std;

extern ScopeStack *gtable;

class BuildSymbol: public Visitor {
public:
    bool failed;
	ScopeStack *table;

    /// \brief constructor
	BuildSymbol(ScopeStack *table) {
		this->table = table;
        failed = 0;
	}

	// Main class must have a main function
	virtual bool isMainClass(Class *c) {
		if (c == 0) {
			return false;
		}

        // push class scope into stack
		table->open(c->associatedScope);
        // lookup main function in Main class scope
		Symbol *main = table->lookup("main", false);

		if (main == 0 || !main->isFunction()) {
			return false;
		}

        // set main
		((Function *) main)->setMain(true);

        // main function: return type must be VOID, parametes must be 0
		FuncType *type = (FuncType *) main->type;
		return type->getReturnType()->equal(BaseType::VOID) && type->numOfParams() == 0;
	}

    /// \brief calculate depth in inheriting tree
	virtual int calcOrder(Class *c) {
		if (c == 0) {
			return -1;
		}
		if (c->order < 0) {
			c->order = 0;
			c->order = calcOrder(c->getParent()) + 1;
		}
		return c->order;
	}

     /// \brief override check
     ///
     /// error cases:
	 /// 1.var cannnot be override
	 /// 2.var override func
	 /// 3.func override var
	 /// 4.return type not compatible
     ///
	 virtual void checkOverride(Class *c) {
		if (c->check) {
			return;
		}

		Class *parent = c->getParent();

        // no parent class
		if (parent == 0) {
			return;
		}

        // recursion
		checkOverride(parent);

		ClassScope *parentScope = parent->associatedScope;
		ClassScope *subScope = c->associatedScope;

		table->open(parentScope);

        for (map<string, Symbol *>::iterator it = symbols->begin();
                it != symbols->end(); it++) {
            Symbol *suspect = it->second;

            // parent symbol
			Symbol *sym = table->lookup(suspect->name, true);

			if (sym != 0 && !sym->isClass()) {
				if ((suspect->isVariable() && sym->isFunction())
						|| (suspect->isFunction() && sym->isVariable())) {
                    failed = 1;
                    dragon_report(suspect->location, "incompatible override: variable/function can't override each other\n");
				} else if (suspect->isFunction() && !suspect->type->compatible(sym->type)) {
                    failed = 1;
                    dragon_report(suspect->location, "incompatible override: different return type\n");
				} else if (suspect->isVariable()) {
                    failed = 1;
                    dragon_report(suspect->location, "variable can't be override\n");
				}
			}
		}

		table->close();
		c->check = true;
	}

	virtual void visitProgram(Program *program) {
		// initialize the program global scope
		program->globalScope = new GlobalScope();

		// push global scope into stack
		table->open(program->globalScope);

		// declare classes in global scope
        for (int i = 0; i < classes->size(); i++) {
            ClassDef *cd = (*classes)[i];
            Class *c = new Class(cd->name, cd->parent, cd->location);
			Class *earlier = table->lookupClass(cd->name);

			if (earlier != 0) {
                failed = 1;
                dragon_report(cd->loc, "redefined class '%s'\n", cd->name);
			} else {
				table->declare(c);
			}

			// bind symbol to ast node
			cd->symbol = c;
        }

        // inheritance check
        for (int i = 0; i < classes->size(); i++) {
            ClassDef *cd = (*classes)[i];
			Class *c = cd->symbol;

			if (cd->parent != 0 && c->getParent() == 0) {
                failed = 1;
                dragon_report(cd->loc, "undefined parent class '%s' of '%s'\n", cd->parent, cd->name);
				c->dettachParent();
			}

            // wrong inheritance in the inheriting tree
            // parent extends children(circular inheritance)
			if (calcOrder(c) <= calcOrder(c->getParent())) {
                failed = 1;
                dragon_report(cd->loc, "bad inheritance between '%s' and '%s'\n", cd->parent, cd->name);
				c->dettachParent();
			}
		}

        // before recursion
		// create class description
        for (int i = 0; i < classes->size(); i++) {
            ClassDef *cd = (*classes)[i];
			cd->symbol->createType();
		}

		// recursion
        for (int i = 0; i < classes->size(); i++) {
            ClassDef *cd = (*classes)[i];
			cd->accept(this);

			if (strcmp("Main", cd->name) {
				program->main = cd->symbol;
			}
		}

        // after recursion
		// override check
		for (ClassDef *cd : program->classes) {
			checkOverride(cd->symbol);
		}

		// main class check
		if (!isMainClass(program->main)) {
            failed = 1;
            dragog_report(program->loc, "missing main class\n");
		}

		table->close();
	}

	virtual void visitClassDef(ClassDef *classDef) {
		table->open(classDef->symbol->associatedScope);

		// recursion
        for (int i = 0; i < fields->size(); i++) {
            Node *f = (*fields)[i];
		    f->accept(this);
	    }

		table->close();
	}

	virtual void visitVarDef(VarDef *varDef) {
		varDef->type->accept(this);

		if (varDef->type->type->equal(BaseType::VOID)) {
            failed = 1;
            dragon_report(varDef->loc, "variable can't be 'void", varDef->name);
			varDef->symbol = new Variable("error", BaseType::ERROR, varDef->location);
			return ;
		}

        // create variable symbol
		Variable *v = new Variable(varDef->name, varDef->type->type, varDef->loc);

		Symbol *sym = table->lookup(varDef->name, true);
		if (sym != 0) {
            // sym can only be member
			if (table->getCurrentScope()->equals(sym->definedIn))) {
                failed = 1;
                dragon_report(v->location, "redefined variable '%s'\n", v-name.c_str());
			} else if ((sym->definedIn->isFormalScope() || sym->definedIn->isLocalScope())) {
                failed = 1;
                dragon_report(v->location, "redefined variable '%s'\n", v-name.c_str());
			} else {
				table->declare(v);
			}
		} else {
			table->declare(v);
		}

        // bind symbol and node
		varDef->symbol = v;
	}

	virtual void visitFuncDef(FuncDef *funcDef) {
        // check return type
		funcDef->returnType->accept(this);

        // create function symbol
		Function *f = new Function(funcDef->name, funcDef->returnType->type, funcDef->body, funcDef->loc);
        // bind symbol and node
		funcDef->symbol = f;

		Symbol *sym = table->lookup(funcDef->name, false);
		if (sym != 0) {
            failed = 1;
            dragon_report(f->location, "redefined function '%s'\n", f->name.c_str());
		} else {
			table->declare(f);
		}

		table->open(f->associatedScope);

        // recursion
        for (int i = 0; i < formals->size(); i++) {
            VarDef *d = (*formals)[i];
			d->accept(this);
			f->appendParam(d->symbol);
		}
		funcDef->body->accept(this);

		table->close();
	}

    /// \brief check variable defination in block(local scope)
	virtual void visitBlock(Block block) {
		block->associatedScope = new LocalScope(block);
		table->open(block->associatedScope);
        for (int i = 0;i < block->size(); i++) {
            Node *s = (*block)[i];
			s->accept(this);
		}
		table->close();
	}

    /// \brief check variable defination in block(local scope)
	virtual void visitForLoop(ForLoop *forLoop) {
		if (forLoop->loopBody != 0) {
			forLoop->loopBody->accept(this);
		}
	}

    /// \brief check variable defination in block(local scope)
	virtual void visitIf(If *ifStmt) {
		if (ifStmt->trueBranch != 0) {
			ifStmt->trueBranch->accept(this);
		}
		if (ifStmt->falseBranch != 0) {
			ifStmt->falseBranch->accept(this);
		}
	}

    /// \brief check variable defination in block(local scope)
	virtual void visitWhileLoop(WhileLoop *whileLoop) {
		if (whileLoop->loopBody != 0) {
			whileLoop->loopBody->accept(this);
		}
	}

	virtual void visitTypeBasic(TypeBasic *type) {
		switch (type->typeKind) {
		    case TYPE_VOID:
			    type->type = BaseType::VOID;
			    break;
		    case TYPE_INT:
			    type->type = BaseType::INT;
			    break;
		    case TYPE_BOOL:
			    type->type = BaseType::BOOL;
			    break;
		    default:
			    type->type = BaseType::STRING;
                break;
		}
	}

	virtual void visitTypeClass(TypeClass *typeClass) {
		Class *c = table->lookupClass(typeClass->name);

		if (c == 0) {
            failed = 1;
            dragon_report(typeClass->loc, "undefined class '%s'\n", typeClass->name);
			typeClass->type = BaseType::ERROR;
		} else {
            // @FIXME getType() in need?
			typeClass->type = c->getType();
		}
	}

	virtual void visitTypeArray(TypeArray *typeArray) {
        // recursion
		typeArray->elementType->accept(this);

		if (typeArray->elementType->type->equal(BaseType::ERROR)) {
			typeArray->type = BaseType::ERROR;
		} else if (typeArray->elementType->type->equal(BaseType::VOID)) {
            failed = 1;
            dragon_report(typeArray->loc, "type of array elements can't be 'void'"\n);
			typeArray->type = BaseType::ERROR;
		} else {
			typeArray->type = new ArrayType(typeArray->elementType->type);
		}
	}
}

class TypeCheck: Visitor {
public:
	ScopeStack *table;
	Function *currentFunction;
    bool failed;

    /// \brief constructor
	TypeCheck(ScopeStack *table) {
		this->table = table;
        failed = 0;
	}

	virtual void visitProgram(Program *program) {
		table->open(program->globalScope);
        for (int i = 0; i < classes->size(); i++) {
            ClassDef *cd = (*classes)[i];
			cd->accept(this);
		}
		table->close();
	}

	virtual void visitClassDef(ClassDef *classDef) {
		table->open(classDef->symbol->associatedScope);
        for (int i = 0; i < fields->size(); i++) {
            Node *f = (*fields)[i];
			f->accept(this);
		}
		table->close();
	}

	virtual void visitFuncDef(FuncDef *func) {
		this->currentFunction = func->symbol;
		table->open(func->symbol->associatedScope);
		func->body->accept(this);
		table->close();
	}

	virtual void visitBlock(Block block) {
		table->open(block->associatedScope);
        for (int i = 0;i < block->size(); i++) {
            Node *s = (*block)[i];
			s->accept(this);
		}
		table->close();
	}

    /// \brief condition expression check
	virtual void checkTestExpr(Expr *expr) {
		expr->accept(this);

		if (!expr->type->equal(BaseType::ERROR) && !expr->type->equal(BaseType::BOOL)) {
            failed = 1;
            dragon_report(expr->loc, "condition expression must be 'bool' type\n");
		}
	}

	virtual void visitWhileLoop(WhileLoop *whileLoop) {
		checkTestExpr(whileLoop->condition);

		if (whileLoop->loopBody != 0) {
			whileLoop->loopBody->accept(this);
		}
	}

	virtual void visitForLoop(ForLoop *forLoop) {
		if (forLoop->init != 0) {
			forLoop->init->accept(this);
		}

		checkTestExpr(forLoop->condition);

		if (forLoop->update != 0) {
			forLoop->update->accept(this);
		}

		if (forLoop->loopBody != 0) {
			forLoop->loopBody->accept(this);
		}
	}

	virtual void visitIf(If *ifStmt) {
		checkTestExpr(ifStmt->condition);

		if (ifStmt->trueBranch != 0) {
			ifStmt->trueBranch->accept(this);
		}

		if (ifStmt->falseBranch != 0) {
			ifStmt->falseBranch->accept(this);
		}
	}

	virtual void visitPrint(Print *printStmt) {
        for (int i = 0; i < exprs->size(); i++) {
            Expr *e = (*exprs)[i];
            // recursion
			e->accept(this);

			if (!e->type->equal(BaseType::ERROR)
                && !e->type->equal(BaseType::BOOL)
				&& !e->type->equal(BaseType::INT)
				&& !e->type->equal(BaseType::STRING)) {
                failed = 1;
                dragon_report(e->loc, "incompatible argument %d type '%s'\n", i+1, e->type->toString());
			}
		}
	}

	virtual void visitReturn(Return returnStmt) {
        // get return type in function scope
		Type *returnType = ((FormalScope *)table->lookForScope(SCOPE_FORMAL))->owner->getReturnType();

		if (returnStmt->expr != 0) {
			returnStmt->expr->accept(this);
		}

		if (returnType->equal(BaseType::VOID)) {
			if (returnStmt->expr != 0) {
                failed = 1;
                dragon_report(returnStmt->loc, "incompatible return type between '%s' and '%s'\n",
						returnType->toString(), returnStmt->expr->type->toString());
			}
		} else if (returnStmt->expr == 0) {
                failed = 1;
                dragon_report(returnStmt->loc, "missing return statement, need '%s'\n", returnType->toString());
		} else if (!returnStmt->expr->type->equal(BaseType::ERROR)
				&& !returnStmt->expr->type->compatible(returnType)) {
                failed = 1;
                dragon_report(returnStmt->loc, "incompatible return type between '%s' and '%s'\n",
						returnType->toString(), returnStmt->expr->type->toString());
		}
	}

	virtual void visitAssign(Assign *assign) {
        // recursion
		assign->left->accept(this);
		assign->expr->accept(this);

		if (!assign->left->type->equal(BaseType::ERROR) &&
        (assign->left->type->isFuncType() || !assign->expr->type->compatible(assign->left->type))) {
            failed = 1;
            dragon_report(assign->loc, "incompatible assignment from '%s' to '%s'\n",
					assign->left->type->toString(), "=", assign->expr->type->toString());
		}
	}

	virtual void visitNull(Null *nullExpr) {
		nullExpr->type = BaseType::NIL;
	}

	virtual void visitReadIntExpr(ReadIntExpr *readIntExpr) {
		readIntExpr->type = BaseType::INT;
	}

	virtual void visitReadLineExpr(ReadLineExpr *readStringExpr) {
		readStringExpr->type = BaseType::STRING;
	}

	virtual void visitIndexed(Indexed *indexed) {
		indexed->lvKind = ARRAY_ELEMENT;

        // recursion
		indexed->array->accept(this);
		if (!indexed->array->type->isArrayType()) {
            failed = 1;
            dragon_report(indexed->array->loc, "subscripted value is neither array nor vector");
			indexed->type = BaseType::ERROR;
		} else {
			indexed->type = ((ArrayType *) indexed->array->type)->elementType;
		}

        // recursion
		indexed->index->accept(this);
		if (!indexed->index->type->equal(BaseType::INT)) {
            failed = 1;
            dragon_report(indexed->loc, "array subscript is not an integer");
		}
	}

	virtual void checkCallExpr(CallExpr *callExpr, Symbol *f) {
        // get receiver type
		Type *receiverType = callExpr->receiver == 0
            // class type
            ? ((ClassScope *)table->lookForScope(SCOPE_CLASS))->owner->type
            // receiver type
            : callExpr->receiver->type;

		if (f == 0) {
            failed = 1;
            dragon_report(callExpr->loc, "undefined method '%s'\n", callExpr->method);
			callExpr->type = BaseType::ERROR;
		} else if (!f->isFunction()) {
            failed = 1;
            dragon_report(callExpr->loc, "field '%s' is not a method\n", callExpr->method);
			callExpr->type = BaseType::ERROR;
		} else {
			Function *func = (Function *) f;

            // bind symbol and node
			callExpr->symbol = func;
			callExpr->type = func->getReturnType();

            // private check
			if (callExpr->receiver != 0 && callExpr->receiver->isClass) {
                // can't access other class's field
                failed = 1;
                dragon_report(ident->loc, "invalid access to private field '%s' in '%s'\n",
						callExpr->method, callExpr->receiver->type->toString());
			}

            // bind method to 'this'
			if (callExpr->receiver == 0) {
				callExpr->receiver = new ThisExpr(callExpr->loc);
				callExpr->receiver->accept(this);
			}

            // recursion
            for (int i = 0; i < actuals->size(); i++) {
                Expr *e = (*actuals)[i];
				e->accept(this);
			}

			List <Type *> *argList = func->type->argList;

			if ((argList->size() - 1) != callExpr->actuals->size()) {
                failed = 1;
                dragon_report(callExpr->loc, "incompatible number of arguments, expected '%d', get '%d'\n",
                        argList->size() - 1, callExpr->actuals->size());
			} else {
                for (int i = 1, j = 0; i < argList->size() && j < callExpr->actuals->size(); i++, j++) {
					Type *t1 = (*argList)[i];

					Expr *e = (*(callExpr->actuals)[i]);
					Type *t2 = e->type;

					if (!t2->equal(BaseType::ERROR) && !t2->compatible(t1)) {
                        failed = 1;
                        dragon_report(e->loc, "incompatible type between '%s' and '%s'\n", t2->toString(), t1->toString);
					}
				}
			}
		}
	}

	virtual void visitCallExpr(CallExpr *callExpr) {
		if (callExpr->receiver == 0) {
			ClassScope *cs = (ClassScope *) table->lookForScope(SCOPE_CLASS);
			checkCallExpr(callExpr, cs->lookupVisible(callExpr->method));
        } else {
            // recursion
		    callExpr->receiver->usedForRef = true;
		    callExpr->receiver->accept(this);

		    if (callExpr->receiver->type->equal(BaseType::ERROR)) {
			    callExpr->type = BaseType::ERROR;
			    return;
		    }

		    if (!callExpr->receiver->type->isClassType()) {
                failed = 1;
                dragon_report(callExpr->loc, "invalid access to '%s' in '%s'\n",
						    callExpr->method, callExpr->receiver->type->toString());
			    callExpr->type = BaseType::ERROR;
			    return;
		    }

		    ClassScope *cs = ((ClassType *)callExpr->receiver->type)->classScope;
		    checkCallExpr(callExpr, cs->lookupVisible(callExpr->method));
        }
 }

	virtual void visitExec(Exec exec){
		exec->expr->accept(this);
	}

	virtual void visitNewArray(NewArray *newArrayExpr) {
        // recursion
		newArrayExpr->elementType->accept(this);

		if (newArrayExpr->elementType->type->equal(BaseType::ERROR)) {
			newArrayExpr->type = BaseType::ERROR;
		} else if (newArrayExpr->elementType->type->equal(BaseType::VOID)) {
            failed = 1;
            dragon_report(newArrayExpr->elementType->location, "type of array elements can't be 'void'"\n);
			newArrayExpr->type = BaseType::ERROR;
		} else {
			newArrayExpr->type = new ArrayType(newArrayExpr->elementType->type);
		}

        // recursion
		newArrayExpr->length->accept(this);

		if (!newArrayExpr->length->type->equal(BaseType::ERROR)
				&& !newArrayExpr->length->type->equal(BaseType::INT)) {
            failed = 1;
            dragon_report(newArrayExpr->length->loc, "array length is not an integer\n");
		}
	}

	virtual void visitNewClass(NewClass *newClass) {
		Class *c = table->lookupClass(newClass->className);
		newClass->symbol = c;

		if (c == 0) {
            failed = 1;
            dragon_report(newClass->loc, "undefined class '%s'\n", newClass->name);
			newClass->type = BaseType::ERROR;
		} else {
			newClass->type = c->getType();
		}
	}

	virtual void visitThisExpr(ThisExpr *thisExpr) {
		thisExpr->type = ((ClassScope *)table->lookForScope(SCOPE_CLASS))->owner->getType();
	}

	virtual void visitIdent(Ident *ident) {
		if (ident->owner == 0) {
			Symbol *v = table->lookupBeforeLocation(ident->name, ident->loc);

			if (v == 0) {
                failed = 1;
                dragon_report(ident->loc, "undefine variable '%s'\n", ident->name);
				ident->type = BaseType::ERROR;
			} else if (v->isVariable()) {
				Variable *var = (Variable *) v;

                // bind symbol and node
				ident->type = var->type;
				ident->symbol = var;

				if (var->isLocalVar()) {
					ident->lvKind = LOCAL_VAR;
				} else if (var->isParam()) {
					ident->lvKind = PARAM_VAR;
				} else {
                    // field
					ident->owner = new ThisExpr(ident->location);
					ident->owner->accept(this);
					ident->lvKind = MEMBER_VAR;
				}
			} else {
                // bind symbol and node
				ident->type = v->type;

				if (v->isClass()) {
					if (ident->usedForRef) {
						ident->isClass = true;
					} else {
                        failed = 1;
                        dragon_report(ident->loc, "undefined variable '%s'\n", ident->name);
						ident->type = BaseType::ERROR;
					}
				}
			}
		} else {
            // recursion: receiver
			ident->owner->usedForRef = true;
			ident->owner->accept(this);

			if (!ident->owner->type->equal(BaseType::ERROR)) {
                // can't access other class fields
				if (ident->owner->isClass || !ident->owner->type->isClassType()) {
                    failed = 1;
                    dragon_report(ident->loc, "invalid access to private field '%s' in '%s'\n",
							ident->name, ident->owner->type->toString());
					ident->type = BaseType::ERROR;
				} else {
					ClassScope *cs = ((ClassType *)ident->owner->type)->classScope();
					Symbol *v = cs->lookupVisible(ident->name);

					if (v == 0) {
                        failed = 1;
                        dragon_report(ident->loc, "invalid access to undefined field '%s' in '%s'\n"
								ident->name, ident->owner->type->toString());
						ident->type = BaseType::ERROR;
					} else if (v->isVariable()) {
						ClassType *thisType = ((ClassScope *)table->lookForScope(SCOPE_CLASS))->owner->getType();
						ident->type = v->type;

						if (!thisType->compatible(ident->owner->type)) {
                            failed = 1;
                            dragon_report(ident->loc, "invalid access to field '%s' in '%s'\n"
									ident->name, ident->owner->type->toString());
						} else {
							ident->symbol = (Variable *)v;
							ident->lvKind = MEMBER_VAR;
						}
					} else {
						ident->type = v->type;
					}
				}
			} else {
				ident->type = BaseType::ERROR;
			}
		}
	}

	virtual void visitTypeBasic(TypeBasic *type) {
		switch (type->typeKind) {
		    case TYPE_VOID:
			    type->type = BaseType::VOID;
			    break;
		    case TYPE_INT:
			    type->type = BaseType::INT;
			    break;
		    case TYPE_BOOL:
			    type->type = BaseType::BOOL;
			    break;
		    default:
			    type->type = BaseType::STRING;
                break;
		}
	}

	virtual void visitTypeClass(TypeClass *typeClass) {
		Class *c = table->lookupClass(typeClass->name);

		if (c == 0) {
            failed = 1;
            dragon_report(typeClass->loc, "undefined class '%s'\n", typeClass->name);
			typeClass->type = BaseType::ERROR;
		} else {
			typeClass->type = c->getType();
		}
	}

	virtual void visitTypeArray(TypeArray *typeArray) {
        // recursion
		typeArray->elementType->accept(this);

		if (typeArray->elementType->type->equal(BaseType::ERROR)) {
			typeArray->type = BaseType::ERROR;
		} else if (typeArray->elementType->type->equal(BaseType::VOID)) {
            failed = 1;
            dragon_report(typeArray->loc, "type of array elements can't be 'void'"\n);
			typeArray->type = BaseType::ERROR;
		} else {
			typeArray->type = new ArrayType(typeArray->elementType->type);
		}
	}

	Type *checkBinaryOp(Expr *left, Expr *right, astKind op, yyltype *loc) {
        // recursion
		left->accept(this);
		right->accept(this);

		if (left->type->equal(BaseType::ERROR) || right->type->equal(BaseType::ERROR)) {
			switch (op) {
			case EXPR_ADD:
			case EXPR_SUB:
			case EXPR_MUL:
			case EXPR_DIV:
				return left->type;
			case EXPR_MOD:
				return BaseType::INT;
			default:
				return BaseType::BOOL;
			}
		}

		bool compatible = false;
		Type *returnType = BaseType::ERROR;

		switch (op) {
		    case EXPR_ADD:
		    case EXPR_SUB:
		    case EXPR_MUL:
		    case EXPR_DIV:
			    compatible = left->type->equals(BaseType::INT)
					    && left->type->equal(right->type);
			    returnType = left->type;
			    break;
		    case EXPR_GT:
		    case EXPR_GE:
		    case EXPR_LT:
		    case EXPR_LE:
			    compatible = left->type->equal(BaseType::INT)
					    && left->type->equal(right->type);
			    returnType = BaseType::BOOL;
			    break;
		    case EXPR_MOD:
			    compatible = left->type->equal(BaseType::INT)
					    && right->type->equal(BaseType::INT);
			    returnType = BaseType::INT;
			    break;
		    case EXPR_EQ:
		    case EXPR_NE:
			    compatible = left->type->compatible(right->type)
					    || right->type->compatible(left->type);
			    returnType = BaseType::BOOL;
			    break;
		    case EXPR_AND:
		    case EXPR_OR:
			    compatible = left->type->equal(BaseType::BOOL)
					    && right->type->equal(BaseType::BOOL);
			    returnType = BaseType::BOOL;
			    break;
		    default:
			    break;
		}

		if (!compatible) {
            failed = 1;
            dragon_report(loc, "incompatible binary operation between '%s' and '%s'\n",
                    left->type->toString(), right->type->toString());
		}

		return returnType;
	}

	virtual void visitBinary(Binary expr) {
		expr->type = checkBinaryOp(expr->left, expr->right, expr->kind, expr->loc);
	}

	virtual void visitUnary(Unary expr) {
		expr->expr->accept(this);

		if(expr->kind == TYPE_NEG){
			if (expr->expr->type->equal(BaseType::ERROR)
					|| expr->expr->type->equal(BaseType::INT)) {
				expr->type = expr->expr->type;
			} else {
                failed =1;
                dragon_report(expr->loc, "incompatible '-' operation on '%s'\n", expr->expr->type->toString());
				expr->type = BaseType::ERROR;
			}
		} else{
			if (!(expr->expr->type->equal(BaseType::BOOL) || expr->expr->type->equal(BaseType::ERROR))) {
                failed =1;
                dragon_report(expr->loc, "incompatible '!' operation on '%s'\n", expr->expr->type->toString());
			}

			expr->type = BaseType::BOOL;
		}
	}

	virtual void visitConstant(Constant *constant) {
		switch (constant->typeKind) {
		    case TYPE_INT:
			    constant->type = BaseType::INT;
			    break;
		    case TYPE_BOOL:
			    constant->type = BaseType::BOOL;
			    break;
		    case TYPE_STRING:
			    constant->type = BaseType::STRING;
			    break;
            default:
                break;
		}
	}
}

#endif /* !SEMANTIC_H */
