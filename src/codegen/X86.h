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

#include <climits>
#include <iostream>
#include <vector>
#include <map>
#include "libs/List.h"
#include "libs/StringUtils.h"
#include "syntax/AstPrinter.h"
#include "ir/Tac.h"
#include "ir/Translater.h"

using namespace std;

class X86 {
public:
	map <string, string> *stringConst;   ///< string to label
    Translater *tr;
	AstPrinter *ap;

    X86(AstPrinter *ap) {
		stringConst = new map<string, string>();
        this->ap = ap;
    }

	virtual string getStringConstLabel(string s) {
        map<string, string>::iterator it = stringConst->find(s);
        string label;

		if (it == stringConst->end()) {
			label = string("_STRING") + stringConst->size();
			(*stringConst)[s] = label;
		}

		return label;
	}

	virtual void emitAsm(Translater *tr) {
        // decorator pattern
        this->tr = tr;

        emitVTables(tr->vtables);
        ap->print("");

        emit("", ".text");
        emitFuncs(tr->funcs);
		ap->print("");

		emitStringConst();
        emitLibFunction();
	}

    virtual void emitFuncs(List <Functy *> *funcs) {
        for (int i = 0; i < funcs->size(); i++) {
            Functy *ft = (*funcs)[i];
		    emitBeginFunc(ft->label);
            emitAsmForFuncty(ft);
            emitEndFunc(ft->label);

		    ap->print("");
        }
    }

    virtual void emitLibFunction(void) {
        emit("", ".text");

        emit("", ".global _ReadInteger");
        emit("_ReadInteger", "");
        emit("", "pushl %ebp");
        emit("", "movl %esp, %ebp");
        emit("", "leal readBuf, %eax");
        emit("", "pushl %eax");
        emit("", "pushl $readFormat");
        emit("", "call scanf");
        emit("", "popl %ebx");
        emit("", "popl %ebx");
        emit("", "leal readBuf, %eax");
        emit("", "pushl %eax");
        emit("", "call atoi");
        emit("", "popl %ebx");
        emit("", "popl %ebx");
        emit("", "leave");
        emit("", "ret");

        emit("", ".global _ReadLine");
        emit("_ReadLine", "");
        emit("", "pushl %ebp");
        emit("", "movl %esp, %ebp");
        emit("", "leal readBuf, %eax");
        emit("", "pushl %eax");
        emit("", "pushl $readFormat");
        emit("", "call scanf");
        emit("", "popl %ebx");
        emit("", "popl %ebx");
        emit("", "leal readBuf, %eax");
        emit("", "leave");
        emit("", "ret");

        emit("", ".global _PrintInt");
        emit("_PrintInt","");
        emit("", "pushl %ebp");
        emit("", "movl %esp, %ebp");
        emit("", "pushl 8(%ebp)");
	    emit("", "pushl $intFormat");
	    emit("", "call printf");
        emit("", "popl %eax");
        emit("", "popl %eax");
        emit("", "leave");
        emit("", "ret");

        emit("", ".global _PrintBool");
	    emit("_PrintBool", "");
        emit("", "pushl %ebp");
	    emit("", "movl %esp, %ebp");
	    emit("", "xorl %eax, %eax");
	    emit("", "cmpl 8(%ebp), %eax");
	    emit("", "je .L_f");
	    emit("", "pushl $trues");
	    emit("", "jmp .L_e");
	    emit(".L_f", "");
	    emit("", "pushl $falses");
	    emit(".L_e", "");
	    emit("", "call printf");
	    emit("", "leave");
	    emit("", "ret");

        emit("", ".global _PrintString");
        emit("_PrintString","");
        emit("", "pushl %ebp");
        emit("", "movl %esp, %ebp");
        emit("", "pushl 8(%ebp)");
	    emit("", "pushl $stringFormat");
	    emit("", "call printf");
        emit("", "popl %eax");
        emit("", "popl %eax");
        emit("", "leave");
        emit("", "ret");

    }

	virtual void emitStringConst(void) {
		emit("", ".data");

        for (map<string, string>::iterator it = stringConst->begin();
                it != stringConst->end(); it++) {
			emit(it->second, ".string " + string("\"") + it->first + string("\""));
        }

        // for lib function(printf)
        emit("intFormat", ".string \"%d\\n\"");
        emit("trues", ".string \"true\\n\"");
        emit("falses", ".string \"false\\n\"");
        emit("stringFormat", ".string \"%s\\n\"");
        emit("readBuf", ".string \"00000000000000000000000000000000000000000000000000\\0\"");
        emit("readFormat", ".string \"%s\"");
        ap->print("");
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
                    emit("", "cmpl %ebx, %eax");
                    emit("", "setg %al");
                    emit("", "movzbl %al, %eax");
				    break;
			    case TAC_GE:
                    emit("", "cmpl %ebx, %eax");
                    emit("", "setge %al");
                    emit("", "movzbl %al, %eax");
				    break;
			    case TAC_EQ:
                    emit("", "cmpl %ebx, %eax");
                    emit("", "sete %al");
                    emit("", "movzbl %al, %eax");
				    break;
			    case TAC_NE:
                    emit("", "cmpl %ebx, %eax");
                    emit("", "setne %al");
                    emit("", "movzbl %al, %eax");
				    break;
			    case TAC_LE:
                    emit("", "cmpl %ebx, %eax");
                    emit("", "setle %al");
                    emit("", "movzbl %al, %eax");
				    break;
			    case TAC_LT:
                    emit("", "cmpl %ebx, %eax");
                    emit("", "setl %al");
                    emit("", "movzbl %al, %eax");
				    break;
                default:
                    break;
        }

        emit("", string("movl $") + tac->op0->id + string(", %edi"));    // op0 temp id
        emit("", "movl %eax, (%esi, %edi, 4)");     // eax => op0reg[id]
    }

    virtual void emitAsmForUnary(Tac *tac) {
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
                        emit("", "leal " + label + ", %eax");
                    }
				    break;
                default:
                    break;
            }

            emit("", "movl %eax, (%esi, %edi, 4)");
    }

    /// \brief read out from stack actuals
    virtual void emitAsmForParams(Tac *tac) {
        if (tac->op0 && tac->op0->isParam && tac->op0->offset != INT_MAX) {
            // get actual
            emit("", string("movl ") + tac->op0->offset + "(%ebp), %eax");

            // move to param regs
            emit("", string("movl $") + tac->op0->id + string(", %edi"));
            emit("", "movl %eax, (%esi, %edi, 4)");
        }

        if (tac->op1 && tac->op1->isParam && tac->op1->offset != INT_MAX) {
            // get actual
            emit("", string("movl ") + tac->op1->offset + "(%ebp), %eax");

            // move to param regs
            emit("", string("movl $") + tac->op1->id + string(", %edi"));
            emit("", "movl %eax, (%esi, %edi, 4)");
        }

        if (tac->op2 && tac->op2->isParam && tac->op2->offset != INT_MAX) {
            // get actual
            emit("", string("movl ") + tac->op2->offset + "(%ebp), %eax");

            // move to param regs
            emit("", string("movl $") + tac->op2->id + string(", %edi"));
            emit("", "movl %eax, (%esi, %edi, 4)");
        }
    }

    /// \brief write back to stack actuals
    virtual void emitAsmForActuals(Tac *tac) {
        if (tac->op0 && tac->op0->isParam && tac->op0->offset != INT_MAX) {
            // get reg value
            emit("", string("movl $") + tac->op0->id + string(", %edi"));
            emit("", "movl (%esi, %edi, 4), %eax");

            // write back
            emit("", string("movl %eax, ") + tac->op0->offset + "(%ebp)");
        }

        if (tac->op1 && tac->op1->isParam && tac->op1->offset != INT_MAX) {
            // get reg value
            emit("", string("movl $") + tac->op1->id + string(", %edi"));
            emit("", "movl (%esi, %edi, 4), %eax");

            // write back
            emit("", string("movl %eax, ") + tac->op1->offset + "(%ebp)");
        }

        if (tac->op2 && tac->op2->isParam && tac->op2->offset != INT_MAX) {
            // get reg value
            emit("", string("movl $") + tac->op2->id + string(", %edi"));
            emit("", "movl (%esi, %edi, 4), %eax");

            // write back
            emit("", string("movl %eax, ") + tac->op2->offset + "(%ebp)");
        }
    }

	virtual void emitAsmForFuncty(Functy *ft) {
		for (Tac *tac = ft->head->next; tac != 0; tac = tac->next) {
            // get actual from stack, move to param regs
            emitAsmForParams(tac);

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
			    case TAC_PARM:
                    emit("", string("movl $") + tac->op0->id + ", %edi");
                    emit("", "movl (%esi, %edi, 4), %eax");
                    emit("", "pushl %eax");
				    break;
			    case TAC_INDIRECT_CALL:
			    case TAC_DIRECT_CALL:
				    emitAsmForCall(tac);
				    break;
			    case TAC_LOAD:
                    emit("", string("movl $") + tac->op1->id + ", %edi");
                    emit("", "movl (%esi, %edi, 4), %ebx");
                    emit("", string("movl ") + tac->op2->value + string("(%ebx), %eax"));
                    emit("", string("movl $") + tac->op0->id + string(", %edi"));    // op0 temp id
                    emit("", "movl %eax, (%esi, %edi, 4)");     // eax => op0reg[id]
				    break;
			    case TAC_STORE:
                    emit("", string("movl $") + tac->op0->id + ", %edi");
                    emit("", "movl (%esi, %edi, 4), %eax");
                    emit("", string("movl $") + tac->op1->id + ", %edi");
                    emit("", "movl (%esi, %edi, 4), %ebx");
                    emit("", string("movl %eax, ") + tac->op2->value + string("(%ebx)"));
				    break;
                case TAC_MARK:
                    emit(tac->label->name, "");
                    break;
			    case TAC_JMP:
                    emit("", "jmp " + tac->label->name);
                    break;
			    case TAC_BEQZ:
			    case TAC_BNEZ:
                    emit("", string("movl $") + tac->op0->id + string(", %edi"));
                    emit("", "movl (%esi, %edi, 4), %eax");
                    emit("", "testl %eax, %eax");

                    if (tac->opc == TAC_BEQZ) {
                        emit("", "je " + tac->label->name);
                    } else {
                        emit("", "jne " + tac->label->name);
                    }

                    break;
			    case TAC_RETURN:
                    // has return statement
                    if (tac->op0) {
                        emit("", string("movl $") + tac->op0->id + string(", %edi"));   // reg id
                        emit("", "movl (%esi, %edi, 4), %eax");    // reg[id] => eax
                    }
				    break;
            }

            // write back to stack actuals
            emitAsmForActuals(tac);
        }
    }

	virtual void emitAsmForCall(Tac *call) {
        // call
		if (call->opc == TAC_DIRECT_CALL) {
            emit("", "call " + call->label->name);
		} else {
            /* // bind actualRegs to paramRegs */
            /* for (int i = 0; i < tr->funcs->size(); i++) { */
            /*     Functy *ft = (*(tr->funcs))[i]; */

            /*     // found function to call */
            /*     if (ft->label->name == call->label->name) { */
            /*         // bind regs */
            /*         vector <int> *pRegs = ft->paramRegs; */
            /*         vector <int> *aRegs = ft->getActualRegs(call); */

            /*         cout << "Functy: " << ft->label->name << endl; */
            /*         for (int i = 0; i < (int)pRegs->size() && i < (int)aRegs->size(); i++) { */
            /*             cout << "pRegs" << i << ": " << (*pRegs)[i] << endl; */
            /*             cout << "aRegs" << i << ": " << (*aRegs)[i] << endl; */
            /*         } */

            /*         for (int i = 0; i < (int)pRegs->size() && i < (int)aRegs->size(); i++) { */
            /*             emit("", string("movl $") + (*aRegs)[i] + string(", %edi"));   // actual reg id */
            /*             emit("", "movl (%esi, %edi, 4), %eax");    // reg[id] => eax */
            /*             emit("", string("movl $") + (*pRegs)[i] + string(", %edi"));   // param reg id */
            /*             emit("", "movl %eax, (%esi, %edi, 4)"); */
            /*         } */

            /*         break; */
            /*     } */
            /* } */

            // method call
            emit("", string("movl $") + call->op1->id + string(", %edi"));   // reg id
            emit("", "movl (%esi, %edi, 4), %eax");    // reg[id] => eax
            emit("", "movl %eax, %edi");
            emit("", "call *%edi");
		}

        // return value
		if (call->op0 != 0) {
            emit("", string("movl $") + call->op0->id + string(", %edi"));   // reg id
            emit("", "movl %eax, (%esi, %edi, 4)");    // eax => reg[id]
		}
	}

	virtual void emitBeginFunc(Label *label) {
		emit("", ".global " + label->name);
		emit(label->name, "");
        emit("", "pushl %ebp");
        emit("", "movl %esp, %ebp");

        // create fake register files
        if (label->name == "main") {
            emit("", "pushl $4000       # 4000/4 = 1000 fake registers");
            emit("", "call malloc");
            emit("", "movl %eax, %esi   # store registers base into %esi");
        }
	}

	virtual void emitEndFunc(Label *label) {
        emit("", "leave");

        // different exit style
        if (label->name == "main") {
            emit("", "pushl $0");
            emit("", "call exit");
        } else {
            emit("", "ret");
        }
    }


	virtual void emitVTables(List <VTable*> *vtables) {
        for (int i = 0; i < vtables->size(); i++) {
            VTable *vt = (*vtables)[i];
			emit("", ".data");
			emit("", ".align 2");
			emit(vt->name, "");
			emit("", ".long " + (vt->parent == 0 ? "0" : vt->parent->name));
			emit("", ".long " + getStringConstLabel(vt->className));

            for (int i = 0; i < (int)vt->entries->size(); i++) {
                Label *l = (*(vt->entries))[i];
				emit("", ".long " + l->name);
			}
			emit("", "");
		}
	}

	virtual void emit(string label, string body) {
		if (label.empty() && body.empty()) {
			ap->print("\n");
		} else {
			if (!label.empty()) {
                ap->print(label + ":");
			}

			if (!body.empty()) {
                ap->print("\t" + body);
			}
		}
    }
};

#endif /* !X86_H */
