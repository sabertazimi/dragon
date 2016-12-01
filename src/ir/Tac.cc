/*!
 * \file Tac.cc
 * \brief
 *
 * \author sabertazimi, <sabertazimi@gmail.com>
 * \version 1.0
 * \date 2016
 * \license MIT
 */

#include "semantic/Symbol.h"
#include "ir/Tac.h"

int Label::labelCount = 0;  ///< for id
int Temp::tempCount = 0;    ///< for id
map<int, Temp*> *Temp::constTempPool = new map<int, Temp*>();

string itoa(int i) {
    stringstream ss;
    string str;
    ss << i;
    ss >> str;
    return string(str);
}

string operator+(string s, int i) {
    return string(s + itoa(i));
}

string operator+(int i, string s) {
    return string(itoa(i) + s);
}

Label::Label(void) {
}

Label::Label(int id, string name, bool target) {
    this->id = id;

    this->name = name;
    this->target = target;
}

/// \brief print out Label information
string Label::toString(void) {
    return name;
}

Temp::Temp(void) {
    offset = INT_MAX;
}

Temp::Temp(int id, string name, int size, int offset) {
    this->id = id;
    this->name = name;
    this->size = size;
    this->offset = offset;
}

bool Temp::isOffsetFixed(void) {
    return offset != INT_MAX;
}

/// \brief @Override
/// @FIXME
bool Temp::equals(Temp *temp) {
    return id == temp->id;
}

/// \brief @Override
int Temp::hashCode(void) {
    return id;
}

/// \brief @Override
string Temp::toString(void) {
    return name;
}



Tac::Tac(tacKind opc, Temp *op0) {
    this->opc = opc;
    this->op0 = op0;
    this->op1 = 0;
    this->op2 = 0;
}

/// \brief create Tac: a := op b
Tac::Tac(tacKind opc, Temp *op0, Temp *op1) {
    this->opc = opc;
    this->op0 = op0;
    this->op1 = op1;
    this->op2 = 0;
}

/// \brief create Tac: a := b op c
Tac::Tac(tacKind opc, Temp *op0, Temp *op1, Temp *op2) {
    this->opc = opc;
    this->op0 = op0;
    this->op1 = op1;
    this->op2 = op2;
}

/// \brief create Tac:
Tac::Tac(tacKind opc, string str) {
    this->opc = opc;
    this->str = str;
}

/// \brief create Tac:
Tac::Tac(tacKind opc, Temp *op0, string str) {
    this->opc = opc;
    this->op0 = op0;
    this->str = str;
}

/// \brief create Tac:
Tac::Tac(tacKind opc, Temp *op0, VTable *vt) {
    this->opc = opc;
    this->op0 = op0;
    this->vt = vt;
}

/// \brief create Tac:
Tac::Tac(tacKind opc, Label *label) {
    this->opc = opc;
    this->label = label;
}

/// \brief create Tac:
Tac::Tac(tacKind opc, Temp *op0, Label *label) {
    this->opc = opc;
    this->op0 = op0;
    this->label = label;
}

string Tac::binanyOpToString(string op) {
    return op0->name + " = (" + op1->name + " " + op + " " + op2->name + ")";
}

string Tac::unaryOpToString(string op) {
    return op0->name + " = " + op + " " + op1->name;
}

string Tac::toString(void) {
    switch (opc) {
        case TAC_ADD:
            return binanyOpToString("+");
        case TAC_SUB:
            return binanyOpToString("-");
        case TAC_MUL:
            return binanyOpToString("*");
        case TAC_DIV:
            return binanyOpToString("/");
        case TAC_MOD:
            return binanyOpToString("%");
        case TAC_NEG:
            return unaryOpToString("-");
        case TAC_LAND:
            return binanyOpToString("&&");
        case TAC_LOR:
            return binanyOpToString("||");
        case TAC_LNOT:
            return unaryOpToString("!");
        case TAC_GTR:
            return binanyOpToString(">");
        case TAC_GEQ:
            return binanyOpToString(">=");
        case TAC_EQU:
            return binanyOpToString("==");
        case TAC_NEQ:
            return binanyOpToString("!=");
        case TAC_LEQ:
            return binanyOpToString("<=");
        case TAC_LES:
            return binanyOpToString("<");
        case TAC_ASSIGN:
            return op0->name + " = " + op1->name;
        case TAC_LOAD_VTBL:
            return op0->name + " = VTBL <" + vt->name + ">";
        case TAC_INDIRECT_CALL:
            if (op0 != 0) {
                return op0->name + " = " + " call " + op1->name;
            } else {
                return "call " + op1->name;
            }
        case TAC_DIRECT_CALL:
            if (op0 != 0) {
                return op0->name + " = " + " call " + label->name;
            } else {
                return "call " + label->name;
            }
        case TAC_RETURN:
            if (op0 != 0) {
                return "return " + op0->name;
            } else {
                return "return <empty>";
            }
        case TAC_BRANCH:
            return "branch " + label->name;
        case TAC_BEQZ:
            return "if (" + op0->name + " == 0) branch " + label->name;
        case TAC_BNEZ:
            return "if (" + op0->name + " != 0) branch " + label->name;
        case TAC_LOAD:
            if (op2->value >= 0) {
                return op0->name + " = *(" + op1->name + " + " + op2->value + ")";
            } else {
                return op0->name + " = *(" + op1->name + " - " + (-op2->value)
                    + ")";
            }
        case TAC_STORE:
            if (op2->value >= 0) {
                return "*(" + op1->name + " + " + op2->value + ") = " + op0->name;
            } else {
                return "*(" + op1->name + " - " + (-op2->value) + ") = "
                    + op0->name;
            }
        case TAC_LOAD_IMM4:
            return op0->name + " = " + op1->value;
        case TAC_LOAD_STR_CONST:
            return op0->name + " = " + str;
        case TAC_MARK:
            return label->name + ":";
        case TAC_PARM:
            return "parm " + op0->name;
        default:
            break;
    }
}
