/*!
 * \file Scope.h
 * \brief
 *
 * \author sabertazimi, <sabertazimi@gmail.com>
 * \version 1.0
 * \date 2016
 * \license MIT
 */

#ifndef SEMA_SCOPE_H
#define SEMA_SCOPE_H

#include "semantic/common.h"
#include "semantic/Symbol.h"

using namespace std;

class Scope {

};

class FormalScope: public Scope{

};

class LocalScope: public Scope{

};

class ClassScope: public Scope{

};

class GlobalScope: public Scope {

};

class ScopeStack{

};

#endif /* !SEMA_SCOPE_H */
