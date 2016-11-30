/*!
 * \file Offset.h
 * \brief
 *
 * \author sabertazimi, <sabertazimi@gmail.com>
 * \version 1.0
 * \date 2016
 * \license MIT
 */

#ifndef IR_OFFSET_H
#define IR_OFFSET_H

typedef enum __oskind__ {
    OS_LOCAL,
    OS_PARAM,
    OS_MEMBER
} osKind;

typedef enum __ossize__ {
    POINTER_SIZE = 4,
    WORD_SIZE = 4,
    DOUBLE_SIZE = 8
} sizeKind;

class OffSet {
    public:
        osKind kind;
        int value;

        static final OffSet LOCAL_COUNTER = new OffsetCounter(OS_LOCAL);
        static final OffSet PARAM_COUNTER = new OffsetCounter(OS_PARAM);
        static final OffSet MEMBER_COUNTER = new OffsetCounter(OS_MEMBER);

        OffSet(osKind kind);

        virtual void reset(void);
        virtual void set(int offset);
        virtual int next(int value);
};

#endif /* !IR_OFFSET_H */
