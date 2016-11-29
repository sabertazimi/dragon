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

#include <string>
#include <map>
#include "libs/List.h"
#include "location.h"
#include "syntax/AstPrinter.h"

using namespace std;

class Block;
class Symbol;
class Function;
class Class;

/// \brief kind of scope(common kind: SCOPE)
typedef enum __scopeKind__ {
    SCOPE = 100,
    SCOPE_GLOBAL,
    SCOPE_CLASS,
    SCOPE_FORMAL,
    SCOPE_LOCAL
} scopeKind;

class Scope {
    public:
        map<string , Symbol *> *symbols;

        /// \brief constructor
        Scope(void);

        virtual scopeKind getKind(void);

        void print(AstPrinter *ap);

        virtual bool isGlobalScope(void);

        virtual bool isClassScope(void);

        virtual bool isLocalScope(void);

        virtual bool isFormalScope(void);

        /// \brief look up function
        virtual Symbol *lookup(string name);

        /// \brief insert function
        virtual void declare(Symbol *symbol);

        /// \brief remove function
        virtual void cancel(Symbol *symbol);
};

class FormalScope: public Scope{
    public:
        Function *owner;
        Block *astNode;

        FormalScope(Function *owner, Block *astNode);

        /// \brief @Override
        virtual scopeKind getKind(void);

        /// \brief @Override
        virtual bool isFormalScope(void);

        /// \brief @Override
        virtual void print(AstPrinter *ap);
};

class LocalScope: public Scope {
    public:
        Block *node;

        LocalScope(Block *node);

        /// \brief @Override
        virtual scopeKind getKind(void);

        /// \brief @Override
        virtual void print(AstPrinter *ap);

        /// \brief @Override
        virtual bool isLocalScope(void);
};

class ClassScope: public Scope{
    public:
        Class *owner;

        ClassScope(Class *owner);

        /// \brief @Override
        virtual bool isClassScope(void);

        virtual ClassScope *getParentScope(void);

        /// \brief @Override
        virtual scopeKind getKind(void);

        /// \brief @Override
        virtual void print(AstPrinter *ap);

        /// \brief judge inheritance relationship
        ///
        /// judge current scope whether is child of scope defining symbol or not
        ///
        /// \param symbol belong to parent symbol
        virtual bool isInherited(Symbol *symbol);

        /// \brief lookup symbol in scope list(bottom-to-up)
        virtual Symbol *lookupVisible(string name);
};

class GlobalScope: public Scope {
    public:
        /// \brief @Override
        virtual bool isGlobalScope(void);

        /// \brief @Override
        virtual scopeKind getKind(void);

        /// \brief @Override
        virtual void print(AstPrinter *ap);
};

class ScopeStack {
    public:
        List <Scope *> *scopeStack;     ///< top: scopeStack[scoep->size()-1]
        GlobalScope *globalScope;

        ScopeStack(void);

        /// \brief look up symbol in scope stack
        /// \param through whether search into stack or not
        virtual Symbol *lookup(string name, bool through);

        /// \brief look up symbol in scope stack
        /// \param location location limits
        virtual Symbol *lookupBeforeLocation(string name, yyltype *loc);

        virtual void declare(Symbol *symbol);

        /// \brief bind global scope and push all new scopes
        virtual void open(Scope *scope);

        /// \brief clear scope stack
        virtual void close(void);

        /// \brief get closest specific kind scope
        /// \param kind kind of scope
        virtual Scope *lookForScope(scopeKind kind);

        virtual Scope *getCurrentScope(void);

        virtual Class *lookupClass(string name);
};

#endif /* !SEMA_SCOPE_H */
