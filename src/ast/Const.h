/*!
 * \file Const.h
 * \brief
 *
 * \author sabertazimi, <sabertazimi@gmail.com>
 * \version 1.0
 * \date 2016
 * \license MIT
 */

#ifndef AST_CONST_H
#define AST_CONST_H

#include "ast/common.h"

using namespace std;

/// \brief constant
class Const: public Node{
public:
    Const(yyltype loc) {
        this->loc = loc;
        this->env = 0;
    }

    /// \brief @override
    virtual bool isConst(void) {
        return true;
    }
};

/// \brief int constant
class ConstInt: public Const{
public:
    int val;

    ConstInt(yyltype loc, int val = 0): Const(loc) {
        this->kind = CONST_INT;
        this->loc = loc;
        this->env = 0;
        this->val = val;
    }

    /// \brief @override
    virtual string toString(void) {
        return string("ConstNum->" + this->val);
    }
};

/// \brief bool constant
class ConstBool: public Const {
public:
    int val;

    ConstBool(yyltype loc, int val = 0): Const(loc) {
        this->kind = CONST_BOOL;
        this->loc = loc;
        this->env = 0;
        this->val = val;
    }

    /// \brief @override
    virtual string toString(void) {
        return string("ConstBool->" + this->val);
    }
};

/// \brief string constant
class ConstString: public Const {
public:
    string text;

    ConstString(yyltype loc, string text = 0): Const(loc) {
        this->kind = CONST_STRING;
        this->loc = loc;
        this->env = 0;
        this->text = text;
    }

    /// \brief @override
    virtual string toString(void) {
        return string("ConstString->" + this->text);
    }
};

/// \brief nil constant
class ConstNil: public Const {
public:
    ConstNil(yyltype loc): Const(loc) {
        this->kind = CONST_NIL;
        this->loc = loc;
        this->env = 0;
    }

    /// \brief @override
    virtual string toString(void) {
        return string("ConstNil");
    }
};

#endif /* !AST_CONST_H */
