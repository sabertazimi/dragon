/*!
 * \file Type.cc
 * \brief Type System(independence of grammar/ast tree)
 *
 * \author sabertazimi, <sabertazimi@gmail.com>
 * \version 1.0
 * \date 2016
 * \license MIT
 */

#include "syntax/Type.h"

using namespace std;

bool Type::isBaseType(void) {
    return false;
}

bool Type::isArrayType(void) {
    return false;
}

bool Type::isFuncType(void) {
    return false;
}

bool Type::isClassType(void) {
    return false;
}

bool BaseType::isBaseType(void) {
    return true;
}

bool BaseType::compatible(Type *type) {
	if (equal(NIL) && type->isClassType()) {
		return true;
    } else {
        return equal(type);
    }
}

	bool BaseType::equal(Type *type) {
        return this == type;
	}

	char *BaseType::toString(void) {
		return typeName;
	}

ArrayType::ArrayType(Type *elementType) {
		this->elementType = elementType;
        typeName = 0;
	}

	/// \brief @Override
	bool ArrayType::compatible(Type *type) {
		return equal(type);
	}

	/// \brief @Override
	bool ArrayType::equal(Type *type) {
		if (!type->isArrayType()) {
			return false;
        } else {
            // equality to type of element
            return elementType->equal(((ArrayType *) type)->elementType);
        }
	}

	/// \brief @Override
	char *ArrayType::toString(void) {
        if (0 == typeName) {
            typeName = new char[strlen(elementType->typeName)+3];
            strcpy(typeName, elementType->typeName);
            strcat(typeName, "[]");
        }

        return typeName;
	}

	/// \brief @Override
	bool ArrayType::isArrayType(void) {
		return true;
	}


FuncType::FuncType(Type *returnType) {
		this->returnType = returnType;
		argList = new List <Type *>();
        typeName = 0;
    }

	/// \brief @Override
	bool FuncType::compatible(Type *type) {
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
	bool FuncType::equal(Type *type) {
        return compatiable(type);
	}

	/// \brief @Override
	char *FuncType::toString(void) {
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
	bool FuncType::isFuncType(void) {
		return true;
	}

    ClassType::ClassType(Class symbol, ClassType *parent) {
		this->symbol = symbol;
		this->parent = parent;
        typeName = 0;
	}

	/// \brief @Override
	bool ClassType::compatible(Type *type) {
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
	bool ClassType::equal(Type *type) {
		return type->isClassType() && symbol == ((ClassType *) type)->symbol;
	}

	/// \brief @Override
	bool ClassType::isClassType(void) {
		return true;
	}

	/// \brief @Override
	char *ClassType::toString(void) {
        if (0 == typeName) {
            typeName = new char[strlen(symbol->name)+10];
            strcpy(typeName, "class: ");
            strcat(typeName, symbol->name);
        }

        return typeName;
	}

	ClassScope ClassType::getClassScope(void) {
		return symbol->AssociatedScope;
	}
