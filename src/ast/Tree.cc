/*!
 * \file Tree.cc
 * \brief
 *
 * \author sabertazimi, <sabertazimi@gmail.com>
 * \version 1.0
 * \date 2016
 * \license MIT
 */

#include "Tree.h"

using namespace std;

bool Node::isClass(void) {
    return false;
}

bool Node::isFunc(void) {
    return false;
}

bool Node::isVar(void) {
    return false;
}

bool Node::isStmt(void) {
    return false;
}

bool Node::isExpr(void) {
    return false;
}

bool Node::isType(void) {
    return false;
}

bool Node::isConst(void) {
    return false;
}

void Node::accept(Visitor v) {
    v.visitNode(this);
}
