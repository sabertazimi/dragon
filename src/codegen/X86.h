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

    X86(AstPrinter *ap);

	virtual string getStringConstLabel(string s);

	virtual void emit(string label, string body);

	virtual void emitAsm(Translater *tr);

	virtual void emitVTables(List <VTable*> *vtables);

	virtual void emitBeginFunc(Label *label);

	virtual void emitEndFunc(Label *label);

    virtual void emitFuncs(List <Functy *> *funcs);

	virtual void emitAsmForFuncty(Functy *ft);

    virtual void emitAsmForBinary(Tac *tac);

    virtual void emitAsmForUnary(Tac *tac);

    virtual void emitAsmForLoadConst(Tac *tac);

    /// \brief read out from stack actuals
    virtual void emitAsmForParams(Tac *tac);

    /// \brief write back to stack actuals
    virtual void emitAsmForActuals(Tac *tac);

	virtual void emitAsmForCall(Tac *call);

    virtual void emitLibFunction(void);

	virtual void emitStringConst(void);
};

#endif /* !X86_H */
