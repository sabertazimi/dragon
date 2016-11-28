/*!
 * \file Const.cc
 * \brief
 *
 * \author sabertazimi, <sabertazimi@gmail.com>
 * \version 1.0
 * \date 2016
 * \license MIT
 */

#include "Const.h"

using namespace std;

Const::Const(yyltype* loc) {
    this->loc = loc;
}

bool Const::isConst(void) {
    return true;
}

ConstInt::ConstInt(yyltype loc, int val = 0): Const(loc) {
    this->kind = CONST_INT;
    this->loc = loc;
    this->val = val;
}

string ConstInt::toString(void) {
    return string("ConstNum->" + this->val);
}

ConstBool::ConstBool(yyltype loc, int val = 0): Const(loc) {
    this->kind = CONST_BOOL;
    this->loc = loc;
    this->val = val;
}

string ConstBool::toString(void) {
    return string("ConstBool->" + this->val);
}

ConstString::ConstString(yyltype loc, string text = 0): Const(loc) {
    this->kind = CONST_STRING;
    this->loc = loc;
    this->text = text;
}

string ConstString::toString(void) {
    return string("ConstString->" + this->text);
}

ConstNil::ConstNil(yyltype loc): Const(loc) {
    this->kind = CONST_NIL;
    this->loc = loc;
}

string ConstNil::toString(void) {
    return string("ConstNil");
}

