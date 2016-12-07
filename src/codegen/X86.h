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

/// \brief X86 class as code generator
///
/// use malloc in main(asm) to create 1000 fake registers(every occupy 4 bytes)
/// use %esi as registers' files base, use %edi as temp id register
/// use %eax/%ebx as intermediate registers
/// use %eax as functions' return type
///
class X86 {
public:
	map <string, string> *stringConst;  ///< string to label
    Translater *tr;                     ///< composite pattern: take Translater as member, get VTable/Functy(Tac) list from tr
	AstPrinter *ap;                     ///< composite pattern: take AstPrinter as member, enable X86 to has print feature

    /// \brief constructor
    /// \param ap AstPrinter
    X86(AstPrinter *ap);

    /// \brief cache pattern: get(when not exist, create a new one) string label
    /// \param s target string
    /// \return label string
	virtual string getStringConstLabel(string s);

    /// \brief emit asm label and asm body(instruction) code
    /// \param label label name to emit("label:\n")
    /// \param body instruction to emit("movl ...")
    /// \return void
	virtual void emit(string label, string body);

    /// \brief top emitter
    /// \param tr get VTable/Functy list to emit
    /// \return void
	virtual void emitAsm(Translater *tr);

    /// \brief emit .data vtables with vtables' list code
    /// \param vtables vtables' list to emit
    /// \return void
	virtual void emitVTables(List <VTable*> *vtables);

    /// \brief emit stack frame set up code
    /// \param label function label
    /// \return void
	virtual void emitBeginFunc(Label *label);

    /// \brief emit stack frame kill code
    /// \param label function label
    /// \return void
	virtual void emitEndFunc(Label *label);

    /// \brief emit instructions with tac list in functy list(main emitter)
    /// \param funcs functy list
    /// \return void
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
