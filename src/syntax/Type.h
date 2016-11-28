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
}

class BaseType: public Type {
private:
    /// \constructor
    BaseType(char *typeName) {
        this->typeName = strdup(typeName);
    }

public:
	static final BaseType *INT = new BaseType("int");
	static final BaseType *BOOL = new BaseType("bool");
	static final BaseType *STRING = new BaseType("string");
	static final BaseType *VOID = new BaseType("void");
	static final BaseType *NIL= new BaseType("null");

	/// \brief @Override
    virtual bool isBaseType(void) {
        return true;
    }

	/// \brief @Override
	virtual bool compatible(Type *type) {
		if (equal(NIL) && type->isClassType()) {
			return true;
        } else {
            return equal(type);
        }
	}

	/// \brief @Override
	virtual bool equal(Type *type) {
        return this == type;
	}

	/// \brief @Override
	virtual char *toString(void) {
		return typeName;
	}
}

class ArrayType: public Type {
public:
    Type *elementType;

    /// \constructor
	ArrayType(Type *elementType) {
		this->elementType = elementType;
        typeName = 0;
	}

	/// \brief @Override
	virtual bool compatible(Type *type) {
		return equal(type);
	}

	/// \brief @Override
	virtual bool equal(Type *type) {
		if (!type->isArrayType()) {
			return false;
        } else {
            // equality to type of element
            return elementType->equal(((ArrayType *) type)->elementType);
        }
	}

	/// \brief @Override
	virtual char *toString(void) {
        if (0 == typeName) {
            typeName = new char[strlen(elementType->typeName)+3];
            strcpy(typeName, elementType->typeName);
            strcat(typeName, "[]");
        }

        return typeName;
	}

	/// \brief @Override
	virtual bool isArrayType(void) {
		return true;
	}
}

virtual class FuncType: public Type {
public:
	Type *returnType;
	List <Type *> *argList;

	FuncType(Type *returnType) {
		this->returnType = returnType;
		argList = new List <Type *>();
        typeName = 0;
    }

	/// \brief @Override
	virtual bool compatible(Type *type) {
        if (!type->isFuncType()) {
            return false;
        } else {
            FuncType ft = (FuncType *) type;

            // different type or arguments
            if (!returnType->compatible(ft->returnType)
	            || argList->size() != ft->argList->size()) {
	                return false;
            } else {
                for (i = 0; i < argList->size(); i++) {
	                if (!ft->argList[i]->compatible(argList[i])) {
	                    return false;
	                }
                }

                return true;
            }
        }
	}

	/// \brief @Override
	virtual bool equal(Type *type) {
        return compatiable(type);
	}

	/// \brief @Override
	virtual char *toString(void) {
        if (0 == typeName) {
            typeName = new char[80];

            // arguments type
            strcpy(typeName, argList[0]->typeName);
            strcat(typeName, "->");

            for (int i = 1; i < argList->size(); i++) {
                strcat(typeName, argList[i]->typeName);
                strcat(typeName, "->");
            }

            // return value type
            strcat(typeName, returnType->typeName);
        }

        return typeName;
	}

	/// \brief @Override
	virtual bool isFuncType(void) {
		return true;
	}
}

virtual class ClassType: public Type {
public:
	Class symbol;
	ClassType *parent;

	ClassType(Class symbol, ClassType *parent) {
		this->symbol = symbol;
		this->parent = parent;
        typeName = 0;
	}

	/// \brief @Override
	virtual bool compatible(Type *type) {
		if (!type->isClassType()) {
			return false;
		}

        // compatiable with inheritance
		for (ClassType *ct = this; ct != 0; ct = ct->parent) {
			if (ct->equal(type)) {
				return true;
			}
		}

		return false;
	}

	/// \brief @Override
	virtual bool equal(Type *type) {
		return type->isClassType() && symbol == ((ClassType *) type)->symbol;
	}

	/// \brief @Override
	virtual bool isClassType(void) {
		return true;
	}

	/// \brief @Override
	virtual char *toString(void) {
        if (0 == typeName) {
            typeName = new char[strlen(symbol->name)+10];
            strcpy(typeName, "class: ");
            strcat(typeName, symbol->name);
        }

        return typeName;
	}

	virtual ClassScope getClassScope(void) {
		return symbol->AssociatedScope;
	}
}

#endif /* !SYNTAX_TYPE_H */
