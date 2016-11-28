/*!
 * \file Symtab.h
 * \brief
 *
 * \author sabertazimi, <sabertazimi@gmail.com>
 * \version 1.0
 * \date 2016
 * \license MIT
 */

#ifndef SEMA_SYMTAB_H
#define SEMA_SYMTAB_H

#include "semantic/common.h"
#include "semantic/Symbol.h"

class ClassScope;

class Symbol{

};

class Variable: public Symbol{

};

class Function: public Symbol{

};

class Class: public Symbol{
public:
    char *name;
    ClassScope *AssociatedScope;
};

#endif /* !SEMA_SYMTAB_H */
