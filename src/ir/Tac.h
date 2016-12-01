/*!
 * \file Tac.h
 * \brief
 *
 * \author sabertazimi, <sabertazimi@gmail.com>
 * \version 1.0
 * \date 2016
 * \license MIT
 */

#ifndef IR_TAC_H
#define IR_TAC_H

#include <climits>
#include <cstdlib>
#include <string>
#include <iostream>
#include <sstream>
#include <map>
#include <set>
#include "libs/List.h"

using namespace std;

// forward defination
class Variable;
class Function;
class Tac;

/// \brief simple helper function for tranfering integer to string
/// \param i integer to tranfer
/// \return integer string
string itoa(int i);

/// \brief @Override enable string can add with integer
/// \param s string
/// \param i integer
/// \return string
string operator+(string s, int i);

/// \brief @Override enable integer can add with string
/// \param s string
/// \param i integer
/// \return string
string operator+(int i, string s);

typedef enum __tacKind__ {
	TAC_ADD,
    TAC_SUB,
    TAC_MUL,
    TAC_DIV,
    TAC_MOD,
    TAC_NEG,
    TAC_LAND,
    TAC_LOR,
    TAC_LNOT,
    TAC_GTR,
    TAC_GEQ,
    TAC_EQU,
    TAC_NEQ,
    TAC_LEQ,
	TAC_LES,
    TAC_ASSIGN,
    TAC_LOAD_VTBL,
    TAC_INDIRECT_CALL,
    TAC_DIRECT_CALL,
    TAC_RETURN,
    TAC_BRANCH,
	TAC_BEQZ,
    TAC_BNEZ,
    TAC_LOAD,
    TAC_STORE,
    TAC_LOAD_IMM4,
    TAC_LOAD_STR_CONST,
    TAC_MARK,
    TAC_PARM
} tacKind;

class Label {
public:
	int id;         ///< label id
	string name;    ///< label name information
	bool target;    ///< whether is the target of jmp instruction
	Tac *where;     ///< label position information
	static int labelCount;  ///< for id

    Label(void);

	Label(int id, string name, bool target);

	static Label *createLabel(void) {
		return createLabel(false);
	}

	static Label *createLabel(bool target) {
		int id = labelCount++;
		return new Label(id, "_L" + id, target);
	}

	static Label *createLabel(string name, bool target) {
		int id = labelCount++;
		return new Label(id, name, target);
	}

	/// \brief print out Label information
	virtual string toString(void);
};

class Temp {
public:
	int id;
	string name;
	int offset;
	int size;
	Variable *sym;
	bool isConst;       ///< whether is constant or not
	int value;
	bool isParam;       ///< whether is parameter of function or not
	bool isLoaded;
	static int tempCount;   ///< for id
	static map<int, Temp*> *constTempPool;

    /// \brief temp(register) comparation function
    static int tempcmp(Temp *o1, Temp *o2) {
		return o1->id > o2->id ? 1 : o1->id == o2->id ? 0 : -1;
	}

	Temp(void);

	Temp(int id, string name, int size, int offset);

	static Temp *createTempI4(void) {
		int id = tempCount++;
		return new Temp(id, "_T" + id, 4, INT_MAX);
	}


	static Temp *createConstTemp(int value) {
        map<int, Temp*>::iterator it = constTempPool->find(value);

		if (it == constTempPool->end()) {
			Temp *temp = new Temp();
			temp->isConst = true;
			temp->value = value;
			temp->name = itoa(value);
			(*constTempPool)[value] = temp;
		    return temp;
        } else {
            return it->second;
        }
	}

	virtual bool isOffsetFixed(void);

	/// \brief @Override
    /// @FIXME
	virtual bool equals(Temp *temp);

	/// \brief @Override
	virtual int hashCode(void);

	/// \brief @Override
	virtual string toString(void);
};

class Functy {
public:
	Label *label;
	Tac *head;
	Tac *tail;
	Function *sym;
};

class VTable {
public:
	string name;
	VTable *parent;
	string className;
	List <Label *> *entries;
};

class Tac {
public:
	tacKind opc;
	bool mark;
	Tac *prev;
	Tac *next;
	Temp *op0;
	Temp *op1;
	Temp *op2;
	Label *label;
	VTable *vt;
	string str;
	int bbNum;
	set <Temp*> *liveOut;
	set <Temp*> *saves;

    /// \brief create Tac:
	Tac(tacKind opc, Temp *op0);

    /// \brief create Tac: a := op b
	Tac(tacKind opc, Temp *op0, Temp *op1);

    /// \brief create Tac: a := b op c
	Tac(tacKind opc, Temp *op0, Temp *op1, Temp *op2);

    /// \brief create Tac:
	Tac(tacKind opc, string str);

    /// \brief create Tac:
	Tac(tacKind opc, Temp *op0, string str);

    /// \brief create Tac:
	Tac(tacKind opc, Temp *op0, VTable *vt);

    /// \brief create Tac:
	Tac(tacKind opc, Label *label);

    /// \brief create Tac:
	Tac(tacKind opc, Temp *op0, Label *label);

	static Tac *emitAdd(Temp *dst, Temp *src1, Temp *src2) {
		return new Tac(TAC_ADD, dst, src1, src2);
	}

	static Tac *emitSub(Temp *dst, Temp *src1, Temp *src2) {
		return new Tac(TAC_SUB, dst, src1, src2);
	}

	static Tac *emitMul(Temp *dst, Temp *src1, Temp *src2) {
		return new Tac(TAC_MUL, dst, src1, src2);
	}

	static Tac *emitDiv(Temp *dst, Temp *src1, Temp *src2) {
		return new Tac(TAC_DIV, dst, src1, src2);
	}

	static Tac *emitMod(Temp *dst, Temp *src1, Temp *src2) {
		return new Tac(TAC_MOD, dst, src1, src2);
	}

	static Tac *emitNeg(Temp *dst, Temp *src) {
		return new Tac(TAC_NEG, dst, src);
	}

	static Tac *emitLAnd(Temp *dst, Temp *src1, Temp *src2) {
		return new Tac(TAC_LAND, dst, src1, src2);
	}

	static Tac *emitLOr(Temp *dst, Temp *src1, Temp *src2) {
		return new Tac(TAC_LOR, dst, src1, src2);
	}

	static Tac *emitLNot(Temp *dst, Temp *src) {
		return new Tac(TAC_LNOT, dst, src);
	}

	static Tac *emitGtr(Temp *dst, Temp *src1, Temp *src2) {
		return new Tac(TAC_GTR, dst, src1, src2);
	}

	static Tac *emitGeq(Temp *dst, Temp *src1, Temp *src2) {
		return new Tac(TAC_GEQ, dst, src1, src2);
	}

	static Tac *emitEqu(Temp *dst, Temp *src1, Temp *src2) {
		return new Tac(TAC_EQU, dst, src1, src2);
	}

	static Tac *emitNeq(Temp *dst, Temp *src1, Temp *src2) {
		return new Tac(TAC_NEQ, dst, src1, src2);
	}

	static Tac *emitLeq(Temp *dst, Temp *src1, Temp *src2) {
		return new Tac(TAC_LEQ, dst, src1, src2);
	}

	static Tac *emitLes(Temp *dst, Temp *src1, Temp *src2) {
		return new Tac(TAC_LES, dst, src1, src2);
	}

	static Tac *emitAssign(Temp *dst, Temp *src) {
		return new Tac(TAC_ASSIGN, dst, src);
	}

	static Tac *emitLoadVtbl(Temp *dst, VTable *vt) {
		return new Tac(TAC_LOAD_VTBL, dst, vt);
	}

	static Tac *emitIndirectCall(Temp *dst, Temp *func) {
		return new Tac(TAC_INDIRECT_CALL, dst, func);
	}

	static Tac *emitDirectCall(Temp *dst, Label *func) {
		return new Tac(TAC_DIRECT_CALL, dst, func);
	}

	static Tac *emitReturn(Temp *src) {
		return new Tac(TAC_RETURN, src);
	}

	static Tac *emitBranch(Label *label) {
		label->target = true;
		return new Tac(TAC_BRANCH, label);
	}

	static Tac *emitBeqz(Temp *cond, Label *label) {
		label->target = true;
		return new Tac(TAC_BEQZ, cond, label);
	}

	static Tac *emitBnez(Temp *cond, Label *label) {
		label->target = true;
		return new Tac(TAC_BNEZ, cond, label);
	}

	static Tac *emitLoad(Temp *dst, Temp *base, Temp *offset) {
		if (!offset->isConst) {
            cerr << "offset must be constant" << endl;
            exit(-1);
		}

		return new Tac(TAC_LOAD, dst, base, offset);
	}

	static Tac *emitStore(Temp *src, Temp *base, Temp *offset) {
		if (!offset->isConst) {
            cerr << "offset must be constant" << endl;
            exit(-1);
		}
		return new Tac(TAC_STORE, src, base, offset);
	}

	static Tac *emitLoadImm4(Temp *dst, Temp *val) {
		if (!val->isConst) {
            cerr << "value must be constant" << endl;
            exit(-1);
		}
		return new Tac(TAC_LOAD_IMM4, dst, val);
	}

	static Tac *emitLoadStrConst(Temp *dst, string str) {
		return new Tac(TAC_LOAD_STR_CONST, dst, str);
	}

	static Tac *emitMark(Label *label) {
		Tac *mark = new Tac(TAC_MARK, label);
		label->where = mark;
		return mark;
	}

	static Tac *emitParm(Temp *src) {
		return new Tac(TAC_PARM, src);
	}

	virtual string binanyOpToString(string op);

	virtual string unaryOpToString(string op);

	virtual string toString(void);
};

#endif /* !IR_TAC_H */
