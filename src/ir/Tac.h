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
#include <string>
#include <map>

using namespace std;

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
    TAC_MEMO,
    TAC_MARK,
    TAC_PARM
} tacKind;

class Label {
public:
	int id;         ///< label id
	string name;    ///< label name information
	bool target;    ///< whether is the target of jmp instruction
	Tac *where;     ///< label position information
	static int labelCount = 0;  ///< for id

    Label(void) {
    }

	Label(int id, string name, bool target) {
		this->id = id;

        this->name = name;
		this->target = target;
	}

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
	virtual string toString(void) {
		return name;
	}
};

class Temp {
	int id;
	string name;
	int offset;
	int size;
	Variable *sym;
	bool isConst;       ///< whether is constant or not
	int value;
	bool isParam;       ///< whether is parameter of function or not
	bool isLoaded;
	static int tempCount = 0;   ///< for id
	static map<int, Temp*> *constTempPool = new map<int, Temp*>();

    /// \brief temp(register) comparation function
    static int tempcmp(Temp *o1, Temp *o2) {
		return o1->id > o2->id ? 1 : o1->id == o2->id ? 0 : -1;
	}

	Temp(void) {
        offset = INT_MAX;
	}

	Temp(int id, string name, int size, int offset) {
		this->id = id;
		this->name = name;
		this->size = size;
		this->offset = offset;
	}

	static Temp *createTempI4(void) {
		int id = tempCount++;
		return new Temp(id, "_T" + id, 4, Integer->MAX_VALUE);
	}


	static Temp *createConstTemp(int value) {
		Temp *temp = constTempPool->get(value);
		if (temp == null) {
			temp = new Temp();
			temp->isConst = true;
			temp->value = value;
			temp->name = Integer->toString(value);
			constTempPool->put(value, temp);
		}
		return temp;
	}

	virtual bool isOffsetFixed(void) {
		return offset != Integer->MAX_VALUE;
	}

	@Override
	virtual bool equals(Object obj) {
		if (obj instanceof Temp) {
			return id == ((Temp) obj)->id;
		}
		return false;
	}

	@Override
	virtual int hashCode(void) {
		return id;
	}

	@Override
	virtual string toString(void) {
		return name;
	}



};

class Functy {
public:
	Label *label;
	Tac *paramMemo;
	Tac *head;
	Tac *tail;
	Function *sym;
};

class VTable {
public:
	string name;
	VTable *parent;
	string className;
	Label *entries[];
};

class Tac *{
	public Kind opc;

	public bool mark;

	public Tac *prev;

	public Tac *next;

	public Temp *op0;

	public Temp *op1;

	public Temp *op2;

	public Label *label;

	public VTable *vt;

	public string str;

	public int bbNum;

	public Set<Temp> liveOut;

	public Set<Temp> saves;

	private Tac(Kind opc, Temp *op0) {
		this(opc, op0, null, null);
	}

	private Tac(Kind opc, Temp *op0, Temp *op1) {
		this(opc, op0, op1, null);
	}

	private Tac(Kind opc, Temp *op0, Temp *op1, Temp *op2) {
		this->opc = opc;
		this->op0 = op0;
		this->op1 = op1;
		this->op2 = op2;
	}

	private Tac(Kind opc, string str) {
		this->opc = opc;
		this->str = str;
	}

	private Tac(Kind opc, Temp *op0, string str) {
		this->opc = opc;
		this->op0 = op0;
		this->str = str;
	}

	private Tac(Kind opc, Temp *op0, VTable *vt) {
		this->opc = opc;
		this->op0 = op0;
		this->vt = vt;
	}

	private Tac(Kind opc, Label *label) {
		this->opc = opc;
		this->label = label;
	}

	private Tac(Kind opc, Temp *op0, Label *label) {
		this->opc = opc;
		this->op0 = op0;
		this->label = label;
	}

	public static Tac *emitAdd(Temp *dst, Temp *src1, Temp *src2) {
		return new Tac(Kind->ADD, dst, src1, src2);
	}

	public static Tac *emitSub(Temp *dst, Temp *src1, Temp *src2) {
		return new Tac(Kind->SUB, dst, src1, src2);
	}

	public static Tac *emitMul(Temp *dst, Temp *src1, Temp *src2) {
		return new Tac(Kind->MUL, dst, src1, src2);
	}

	public static Tac *emitDiv(Temp *dst, Temp *src1, Temp *src2) {
		return new Tac(Kind->DIV, dst, src1, src2);
	}

	public static Tac *emitMod(Temp *dst, Temp *src1, Temp *src2) {
		return new Tac(Kind->MOD, dst, src1, src2);
	}

	public static Tac *emitNeg(Temp *dst, Temp *src) {
		return new Tac(Kind->NEG, dst, src);
	}

	public static Tac *emitLAnd(Temp *dst, Temp *src1, Temp *src2) {
		return new Tac(Kind->LAND, dst, src1, src2);
	}

	public static Tac *emitLOr(Temp *dst, Temp *src1, Temp *src2) {
		return new Tac(Kind->LOR, dst, src1, src2);
	}

	public static Tac *emitLNot(Temp *dst, Temp *src) {
		return new Tac(Kind->LNOT, dst, src);
	}

	public static Tac *emitGtr(Temp *dst, Temp *src1, Temp *src2) {
		return new Tac(Kind->GTR, dst, src1, src2);
	}

	public static Tac *emitGeq(Temp *dst, Temp *src1, Temp *src2) {
		return new Tac(Kind->GEQ, dst, src1, src2);
	}

	public static Tac *emitEqu(Temp *dst, Temp *src1, Temp *src2) {
		return new Tac(Kind->EQU, dst, src1, src2);
	}

	public static Tac *emitNeq(Temp *dst, Temp *src1, Temp *src2) {
		return new Tac(Kind->NEQ, dst, src1, src2);
	}

	public static Tac *emitLeq(Temp *dst, Temp *src1, Temp *src2) {
		return new Tac(Kind->LEQ, dst, src1, src2);
	}

	public static Tac *emitLes(Temp *dst, Temp *src1, Temp *src2) {
		return new Tac(Kind->LES, dst, src1, src2);
	}

	public static Tac *emitAssign(Temp *dst, Temp *src) {
		return new Tac(Kind->ASSIGN, dst, src);
	}

	public static Tac *emitLoadVtbl(Temp *dst, VTable *vt) {
		return new Tac(Kind->LOAD_VTBL, dst, vt);
	}

	public static Tac *emitIndirectCall(Temp *dst, Temp *func) {
		return new Tac(Kind->INDIRECT_CALL, dst, func);
	}

	public static Tac *emitDirectCall(Temp *dst, Label *func) {
		return new Tac(Kind->DIRECT_CALL, dst, func);
	}

	public static Tac *emitReturn(Temp *src) {
		return new Tac(Kind->RETURN, src);
	}

	public static Tac *emitBranch(Label *label) {
		label->target = true;
		return new Tac(Kind->BRANCH, label);
	}

	public static Tac *emitBeqz(Temp *cond, Label *label) {
		label->target = true;
		return new Tac(Kind->BEQZ, cond, label);
	}

	public static Tac *emitBnez(Temp *cond, Label *label) {
		label->target = true;
		return new Tac(Kind->BNEZ, cond, label);
	}

	public static Tac *emitLoad(Temp *dst, Temp *base, Temp *offset) {
		if (!offset->isConst) {
			throw new IllegalArgumentException("offset must be const temp");
		}
		return new Tac(Kind->LOAD, dst, base, offset);
	}

	public static Tac *emitStore(Temp *src, Temp *base, Temp *offset) {
		if (!offset->isConst) {
			throw new IllegalArgumentException("offset must be const temp");
		}
		return new Tac(Kind->STORE, src, base, offset);
	}

	public static Tac *emitLoadImm4(Temp *dst, Temp *val) {
		if (!val->isConst) {
			throw new IllegalArgumentException("val must be const temp");
		}
		return new Tac(Kind->LOAD_IMM4, dst, val);
	}

	public static Tac *emitLoadStrConst(Temp *dst, string str) {
		return new Tac(Kind->LOAD_STR_CONST, dst, str);
	}

	public static Tac *emitMemo(string memo) {
		return new Tac(Kind->MEMO, memo);
	}

	public static Tac *emitMark(Label *label) {
		Tac *mark = new Tac(Kind->MARK, label);
		label->where = mark;
		return mark;
	}

	public static Tac *emitParm(Temp *src) {
		return new Tac(Kind->PARM, src);
	}

	private string binanyOpToString(string op) {
		return op0->name + " = (" + op1->name + " " + op + " " + op2->name + ")";
	}

	private string unaryOpToString(string op) {
		return op0->name + " = " + op + " " + op1->name;
	}

	public string toString(void) {
		switch (opc) {
		case ADD:
			return binanyOpToString("+");
		case SUB:
			return binanyOpToString("-");
		case MUL:
			return binanyOpToString("*");
		case DIV:
			return binanyOpToString("/");
		case MOD:
			return binanyOpToString("%");
		case NEG:
			return unaryOpToString("-");
		case LAND:
			return binanyOpToString("&&");
		case LOR:
			return binanyOpToString("||");
		case LNOT:
			return unaryOpToString("!");
		case GTR:
			return binanyOpToString(">");
		case GEQ:
			return binanyOpToString(">=");
		case EQU:
			return binanyOpToString("==");
		case NEQ:
			return binanyOpToString("!=");
		case LEQ:
			return binanyOpToString("<=");
		case LES:
			return binanyOpToString("<");
		case ASSIGN:
			return op0->name + " = " + op1->name;
		case LOAD_VTBL:
			return op0->name + " = VTBL <" + vt->name + ">";
		case INDIRECT_CALL:
			if (op0 != null) {
				return op0->name + " = " + " call " + op1->name;
			} else {
				return "call " + op1->name;
			}
		case DIRECT_CALL:
			if (op0 != null) {
				return op0->name + " = " + " call " + label->name;
			} else {
				return "call " + label->name;
			}
		case RETURN:
			if (op0 != null) {
				return "return " + op0->name;
			} else {
				return "return <empty>";
			}
		case BRANCH:
			return "branch " + label->name;
		case BEQZ:
			return "if (" + op0->name + " == 0) branch " + label->name;
		case BNEZ:
			return "if (" + op0->name + " != 0) branch " + label->name;
		case LOAD:
			if (op2->value >= 0) {
				return op0->name + " = *(" + op1->name + " + " + op2->value + ")";
			} else {
				return op0->name + " = *(" + op1->name + " - " + (-op2->value)
						+ ")";
			}
		case STORE:
			if (op2->value >= 0) {
				return "*(" + op1->name + " + " + op2->value + ") = " + op0->name;
			} else {
				return "*(" + op1->name + " - " + (-op2->value) + ") = "
						+ op0->name;
			}
		case LOAD_IMM4:
			return op0->name + " = " + op1->value;
		case LOAD_STR_CONST:
			return op0->name + " = " + MiscUtils->quote(str);
		case MEMO:
			return "memo '" + str + "'";
		case MARK:
			return label->name + ":";
		case PARM:
			return "parm " + op0->name;
		default:
			throw new RuntimeException("unknown opc");
		}
	}
};

#endif /* !IR_TAC_H */
