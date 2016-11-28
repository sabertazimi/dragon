/*!
 * \file Symbol.h
 * \brief
 *
 * \author sabertazimi, <sabertazimi@gmail.com>
 * \version 1.0
 * \date 2016
 * \license MIT
 */

#ifndef SEMA_SYMBOL_H
#define SEMA_SYMBOL_H

#include <string>

using namespace std;

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

#endif /* !SEMA_SYMBOL_H */
