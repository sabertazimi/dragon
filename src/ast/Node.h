/*!
 * \file Node.h
 * \brief
 *
 * \author sabertazimi, <sabertazimi@gmail.com>
 * \version 1.0
 * \date 2016
 * \license MIT
 */

#ifndef AST_NODE_H
#define AST_NODE_H

#include <string>

using namespace std;

typedef enum __ast_kind__ {
    CONST_INT = 1,
    CONST_BOOL,
    CONST_STRING,
    CONST_NIL
} ast_kind ;

class Node {
public:
    ast_kind kind;      ///< kind of node
    yyltype loc;        ///< location information
    scope_t env;        ///< environment scope

    /// \brief generate information of node
    /// \return information string
    virtual string toString(void);

    /// \brief type check function
    /// \return bool
    virtual bool isClass(void);

    /// \brief type check function
    /// \return bool
    virtual bool isFunc(void);

    /// \brief type check function
    /// \return bool
    virtual bool isStmt(void);

    /// \brief type check function
    /// \return bool
    virtual bool isExpr(void);

    /// \brief type check function
    /// \return bool
    virtual bool isConst(void);
};

#endif /* !AST_NODE_H */
