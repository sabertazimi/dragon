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
class Const: public Node {
    public:
        Const(yyltype loc);

        /// \brief @override
        virtual bool isConst(void);
};

/// \brief int constant
class ConstInt: public Const {
    public:
        int val;

        ConstInt(yyltype loc, int val);

        /// \brief @override
        virtual string toString(void);
};

/// \brief bool constant
class ConstBool: public Const {
    public:
        int val;

        ConstBool(yyltype loc, int val);

        /// \brief @override
        virtual string toString(void);
};

/// \brief string constant
class ConstString: public Const {
    public:
        string text;

        ConstString(yyltype loc, string text);

        /// \brief @override
        virtual string toString(void);
};

/// \brief nil constant
class ConstNil: public Const {
    public:
        ConstNil(yyltype loc);

        /// \brief @override
        virtual string toString(void);
};

#endif /* !AST_CONST_H */
