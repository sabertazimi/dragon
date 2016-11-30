/*!
 * \file Offset.cc
 * \brief
 *
 * \author sabertazimi, <sabertazimi@gmail.com>
 * \version 1.0
 * \date 2016
 * \license MIT
 */

#include "Offset.h"

///< initial value for different scope
const static int initValue[] = {
    -2 * WORD_SIZE,     ///< stack frame
    WORD_SIZE,
    POINTER_SIZE        ///< this pointer, pointing to virtaul function table of class
};

///< offset increase drection
const static int direction[] = {
    -1,                 ///< stack frame
    1,
    1
};

OffSet *OffSet::LOCAL_COUNTER = new OffSet(OS_LOCAL);
OffSet *OffSet::PARAM_COUNTER = new OffSet(OS_PARAM);
OffSet *OffSet::MEMBER_COUNTER = new OffSet(OS_MEMBER);

OffSet::OffSet(osKind kind) {
    this->kind = kind;
    reset();
}

void OffSet::reset(void) {
    value = initValue[kind];
}

void OffSet::set(int offset) {
    value = offset;
}

int OffSet::next(int value) {
    int ret = this->value;
    this->value += direction[kind] * value;
    return ret;
}

