/*!
 * \file X86.h
 * \brief
 *
 * \author sabertazimi, <sabertazimi@gmail.com>
 * \version 1.0
 * \date 2016
 * \license MIT
 */

#ifndef X86_H
#define X86_H

#include <iostream>
#include <map>
#include "libs/List.h"
#include "libs/StringUtils.h"
#include "syntax/AstPrinter.h"
#include "ir/Tac.h"
#include "ir/Translater.h"

using namespace std;

typedef unsigned int genRegs;

typedef enum __speRegKind__ {
      R_CS, R_DS, R_SS, R_ES, R_FS, R_GS,   ///< segment registers
      R_EBP, R_ESP,                         ///< stack registers
      numRegs
} speRegKind;

class speReg {
public:
    speRegKind kind;    ///< specifig register id
    string name;

    speReg(speRegKind kind, string name) {
        this->kind = kind;
        this->name = name;
    }

    virtual string toString(void) {
        return this->name;
    }
};

class X86 {
public:
    genRegs *genRegs;     ///< take memory as general purpose register(remove register allocator)
    map<int, speReg *> *speRegs;
    FrameManager *frameManager;
	map<string, string> *stringConst;   ///< string to label
	AstPrinter *ap;

    X86(AstPrinter *ap) {
        genRegs = new int[500];
        speRegs[R_CS] = new speReg(R_CS, "%cs");
        speRegs[R_DS] = new speReg(R_DS, "%ds");
        speRegs[R_SS] = new speReg(R_SS, "%ss");
        speRegs[R_ES] = new speReg(R_ES, "%es");
        speRegs[R_FS] = new speReg(R_FS, "%fs");
        speRegs[R_GS] = new speReg(R_GS, "%gs");
        speRegs[R_EBP] = new speReg(R_EBP, "%ebp");
        speRegs[R_ESP] = new speReg(R_ESP, "%esp");
		frameManager = new FrameManager();
		stringConst = new map<string, string>();
        this->ap = ap;
    }

	virtual string getStringConstLabel(string s) {
        map<string, string>::iterator it = stringConst->find(s);

		if (it == stringConst->end()) {
			label = "_STRING" + stringConst->size();
			stringConst[s] = label;
		}

		return label;
	}

	virtual void emitAsm(Translater *tr) {
		emit("", ".text");
        emitVTables(tr->vtables);
        emitFuncs(tr->funcs);

		ap->print("");

		emitStringConst();
	}

    virtual void emitFuncs(List <Functy *> *funcs) {
        for (int i = 0; i < funcs->size(); i++) {
            Functy *ft = (*funcs)[i];
		    emitProlog(g->getFuncty()->label, frameManager->getStackFrameSize());
            emitAsmForFuncty(ft);
		    ap->print("");
        }
    }

	virtual void emitStringConst() {
		emit("", ".data");
        for (map<string, string>::iterator it = stringConst->begin();
                it != stringConst->end(); it++) {
			emit(it->second, ".asciiz " + it->first);
        }
	}

    virtual void emitAsmForBinary(Tac *tac) {
        emit("", string("movl $") + tac->op1->id + string(", %edi"));    // op1 temp id
        emit("", "movl (%esi, %edi, 4), %eax");     // op1reg[id] => eax
        emit("", string("movl $") + tac->op2->id + string(", %edi"));    // op2 temp id
        emit("", "movl (%esi, %edi, 4), %ebx");     // op2reg[id] => ebx

        switch(tac->opc) {
                case TAC_ADD:
                    emit("", "addl %ebx, %eax");
				    break;
			    case TAC_SUB:
                    emit("", "subl %ebx, %eax");
				    break;
			    case TAC_MUL:
                    emit("", "imull %ebx, %eax");
				    break;
			    case TAC_DIV:
                    emit("", "movl $0, %edx");
                    emit("", "divl %ebx");
				    break;
			    case TAC_MOD:
                    emit("", "movl $0, %edx");
                    emit("", "divl %ebx");
                    emit("", "movl %edx, %eax");    // move mod from edx to eax
				    break;
			    case TAC_AND:
                    emit("", "andl %ebx, %eax");
				    break;
			    case TAC_OR:
                    emit("", "orl %ebx, %eax");
				    break;
			    case TAC_GT:
                    emit("", "cmpl %ebx, %eax")
                    emit("", "setg %al");
                    emit("", "movzbl %al, %eax");
				    break;
			    case TAC_GE:
                    emit("", "cmpl %ebx, %eax")
                    emit("", "setge %al");
                    emit("", "movzbl %al, %eax");
				    break;
			    case TAC_EQ:
                    emit("", "cmpl %ebx, %eax")
                    emit("", "sete %al");
                    emit("", "movzbl %al, %eax");
				    break;
			    case TAC_NE:
                    emit("", "cmpl %ebx, %eax")
                    emit("", "setne %al");
                    emit("", "movzbl %al, %eax");
				    break;
			    case TAC_LE:
                    emit("", "cmpl %ebx, %eax")
                    emit("", "setle %al");
                    emit("", "movzbl %al, %eax");
				    break;
			    case TAC_LT:
                    emit("", "cmpl %ebx, %eax")
                    emit("", "setl %al");
                    emit("", "movzbl %al, %eax");
				    break;
			    case TAC_LOAD:
                    emit("", "movl (%eax, %ebx, 1), %eax");
				    break;
                default:
                    break;
        }

        emit("", string("movl $") + tac->op0->id + string(", %edi"));    // op0 temp id
        emit("", "movl %eax, (%esi, %edi, 4)");     // eax => op0reg[id]
    }

    emitAsmForUnary(Tac *tac) {
        emit("", string("movl $") + tac->op1->id + string(", %edi"));    // op1 temp id
        emit("", "movl (%esi, %edi, 4), %eax");     // op1reg[id] => eax

        switch(tac->opc) {
                case TAC_NEG:
                    emit("", "negl %eax");
				    break;
			    case TAC_NOT:
                    emit("", "notl %eax");
				    break;
                default:
                    break;
        }

        emit("", string("movl $") + tac->op0->id + string(", %edi"));    // op0 temp id
        emit("", "movl %eax, (%esi, %edi, 4)");     // eax => op0reg[id]
    }

    virtual void emitAsmForLoadConst(Tac *tac) {
            emit("", string("movl $") + tac->op0->id + string(", %edi"));

            switch (tac->opc) {
                case TAC_LOAD_VTBL:
                    emit("", "leal " + tac->vt->name + ", %eax");
				    break;
			    case TAC_LOAD_IMM4:
                    emit("", string("movl $") + tac->op1->value + string(", %eax"));
				    break;
			    case TAC_LOAD_STR_CONST:
                    {
				        string label = getStringConstLabel(tac->str);
                        emit("", "leal" + label + ", %eax");
                    }
				    break;
                default:
                    break;
            }

            emit("", "movl %eax, (%esi, %edi, 4)");
    }

	virtual void emitAsmForFuncty(Functy *ft) {
		for (Tac *tac = ft->head; tac != 0; tac = tac->next) {
			switch (tac->opc) {
                case TAC_ADD:
			    case TAC_SUB:
			    case TAC_MUL:
			    case TAC_DIV:
			    case TAC_MOD:
			    case TAC_AND:
			    case TAC_OR:
			    case TAC_GT:
			    case TAC_GE:
			    case TAC_EQ:
			    case TAC_NE:
			    case TAC_LE:
			    case TAC_LT:
                    emitAsmForBinary(tac);
				    break;
			   	case TAC_NEG:
			    case TAC_NOT:
			    case TAC_ASSIGN:
                    emitAsmForUnary(tac);
				    break;
			    case TAC_LOAD_VTBL:
			    case TAC_LOAD_IMM4:
			    case TAC_LOAD_STR_CONST:
                    emitAsmForLoadConst(tac);
				    break;
			    case TAC_INDIRECT_CALL:
			    case TAC_DIRECT_CALL:
				    emitAsmForCall(ft, tac);
				    break;
			    case TAC_STORE:
                    emit("", string("movl $") + tac->op0->id + ", %edi");
                    emit("", "movl (%esi, %edi, 4), %eax");
                    emit("", string("movl $") + tac->op1->id + ", %edi");
                    emit("", "movl (%esi, %edi, 4), %ebx");
                    emit("", string("movl $") + tac->op2->id + ", %edi");
                    emit("", "movl (%esi, %edi, 4), %ecx");

                    emit("", "movl %eax, (%ebx, %ecx, 1)");
				    break;
			    case TAC_PARM:
                    /* empty */
				    break;
			    case TAC_JMP:
                    emit("", "jmp " + tac->label->name);
                    break;
			    case TAC_BEQZ:
			    case TAC_BNEZ:
                    emit("", string("movl $") + tac->op0->id + string("%edi"));
                    emit("", "movl (%esi, %edi, 4), %eax");
                    emit("", "testl %eax, %eax");

                    if (tac->opc == TAC_BEQZ) {
                        emit("", "je" + tac->label->name);
                    } else {
                        emit("", "jne" + tac->label->name);
                    }

                    break;
			    case TAC_RETURN:
                    emit("", "movl $" + op0->id + ", %edi");   // reg id
                    emit("", "movl (%esi, %edi, 4), %eax");    // reg[id] => eax
                    emit("", "leave");
                    emit("", "ret");
				    break;
			    case TAC_PARM:
                    /* empty */
				    break;
            }
		}
	}

	virtual void emitAsmForCall(Functy *ft, Tac call) {
		if (call->opc == TAC_DIRECT_CALL) {
            emit("", "call " + call->label);
		} else {
            emit("", "movl $" + op1->id + ", %edi");   // reg id
            emit("", "movl (%esi, %edi, 4), %ebx");    // reg[id] => ebx
            emit("", "call *%ebx");
		}

        // return value
		if (call->op0 != 0) {
            emit("", "movl $" + op0->id + ", %edi");   // reg id
            emit("", "movl %eax, (%esi, %edi, 4)");    // eax => reg[id]
		}
	}

	public void emitProlog(Label entryLabel, int frameSize) {
		emit(entryLabel->name, "");
        emit("", "pushl %ebp");
        emit("", "movl %esp, %ebp");
        // emit("", string("addl") + (-frameSize - 2 * POINTER_SIZE));
	}

	virtual void emitVTables(List <VTable*> *vtables) {
		emit("", ".text");
		emit("", ".globl main");

        for (int i = 0; i < vtables->size(); i++) {
            VTable *vt = (*vtables)[i];
			emit("", "");
			emit("", ".data");
			emit("", ".align 2");
			emit(vt->name, "");
			emit("", ".word " + (vt->parent == null ? "0" : vt->parent->name));
			emit("", ".word " + getStringConstLabel(vt->className));

            for (int i = 0; i < vt->entries->size(); i++) {
                Label **l = (*(vt->entries))[i];
				emit("", ".word " + l->name);
			}
		}
	}

	virtual string emitToString(string label, string body) {
		if (label.empty() && body.empty()) {
			return "\n";
		} else {
            char buffer[80];
			if (!label.empty()) {
				if (!body.empty()) {
                    sprintf(buffer, "%-40s:", label->c_str());
				} else {
                    sprintf(buffer, "%s:", label->c_str());
				}
			}
			if (!body.empty()) {
                sprintf(buffer, "          %-30s", body->c_str());
			}

            return string(buffer);
		}
	}

	virtual void emit(string label, string body) {
		ap->print(emitToString(label, body));
	}
};

#endif /* !X86_H */
