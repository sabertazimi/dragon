/*!
 * \file FrameManager.h
 * \brief
 *
 * \author sabertazimi, <sabertazimi@gmail.com>
 * \version 1.0
 * \date 2016
 * \license MIT
 */

#ifndef FRAMEMANAGER_H
#define FRAMEMANAGER_H

#include "ir/OffsetCounter.h"

class FrameManager {
public
	int maxSize;
	int currentSize;
	int maxActualSize;
	int currentActualSize;

    FrameManager(void) {
		maxSize = currentSize = 0;
		maxActualSize = currentActualSize = 4;      ///< for 'this' pointer
    }

	virtual int getStackFrameSize(void) {
		return maxSize + maxActualSize;
	}

	void reset(void) {
		maxSize = currentSize = 0;
		maxActualSize = currentActualSize = 4;
        OffsetCounter::LOCAL_COUNTER->reset();
	}

	void findSlot(Set<Temp> saves) {
		for (Temp temp : saves) {
			findSlot(temp);
		}
	}

	void findSlot(Temp temp) {
		if (temp.isOffsetFixed()) {
			return;
		}
		temp.offset = OffsetCounter.LOCAL_OFFSET_COUNTER.next(temp.size);
		currentSize += temp.size;
		if (currentSize > maxSize) {
			maxSize = currentSize;
		}
	}

	int addActual(Temp temp) {
		int offset = currentActualSize;
		currentActualSize += temp.size;
		return offset;
	}

	void finishActual(void) {
		if (currentActualSize > maxActualSize) {
			maxActualSize = currentActualSize;
		}
		currentActualSize = 4;
	}
};

#endif /* !FRAMEMANAGER_H */
