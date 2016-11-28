/*!
 * \file Type.h
 * \brief Type System(independence of grammar/ast tree)
 *
 * \author sabertazimi, <sabertazimi@gmail.com>
 * \version 1.0
 * \date 2016
 * \license MIT
 */

#ifndef SYNTAX_TYPE_H
#define SYNTAX_TYPE_H

#include <cstring>
#include "libs/List.h"
#include "semantic/Scope.h"
#include "semantic/Symbol.h"

class Type {
public:
	char *typeName;

    /// \brief constructor
    Type(void);

    // type check functions

	virtual bool isBaseType(void);
	virtual bool isArrayType(void);
	virtual bool isFuncType(void);
	virtual bool isClassType(void);

    /// \brief judge compatible of two types
	virtual bool compatible(Type *type);

    /// \brief judge euqality of two types
	virtual bool equal(Type *type);

    /// \brief get type name
	virtual char *toString(void);
};

class BaseType: public Type {
public:
	static BaseType *INT;
	static BaseType *BOOL;
	static BaseType *STRING;
	static BaseType *VOID;
	static BaseType *NIL;

    /// \constructor
    BaseType(const char *typeName);

	/// \brief @Override
    virtual bool isBaseType(void);

	/// \brief @Override
	virtual bool compatible(Type *type);

	/// \brief @Override
	virtual bool equal(Type *type);

	/// \brief @Override
	virtual char *toString(void);
};

class ArrayType: public Type {
public:
    Type *elementType;

    /// \constructor
	ArrayType(Type *elementType);

	/// \brief @Override
	virtual bool compatible(Type *type);

	/// \brief @Override
	virtual bool equal(Type *type);

	/// \brief @Override
	virtual char *toString(void);

	/// \brief @Override
	virtual bool isArrayType(void);
};

class FuncType: public Type {
public:
	Type *returnType;
	List <Type *> *argList;

	FuncType(Type *returnType);

	/// \brief @Override
	virtual bool compatible(Type *type);

	/// \brief @Override
	virtual bool equal(Type *type);

	/// \brief @Override
	virtual char *toString(void);

	/// \brief @Override
	virtual bool isFuncType(void);
};

class ClassType: public Type {
public:
	Class *symbol;
	ClassType *parent;

	ClassType(Class *symbol, ClassType *parent);

	/// \brief @Override
	virtual bool compatible(Type *type);

	/// \brief @Override
	virtual bool equal(Type *type);

	/// \brief @Override
	virtual bool isClassType(void);

	/// \brief @Override
	virtual char *toString(void);

	virtual ClassScope *getClassScope(void);
};

#endif /* !SYNTAX_TYPE_H */
