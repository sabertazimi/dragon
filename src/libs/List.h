/*!
 * \file List.h
 * \brief
 *
 * \author sabertazimi, <sabertazimi@gmail.com>
 * \version 1.0
 * \date 2016
 * \license MIT
 */

#ifndef LIBS_LIST_H
#define LIBS_LIST_H

#include <iostream>
#include <deque>

using namespace std;

template <class Element>
class List {
private:
	deque <Element> elems;

public:
	/// \brief create a new empty list
	List(void) {
	}

	/// \brief number of elements
	/// \return number
	int size(void) {
		return elems.size();
	}

	/// \breif get elements
	Element operator[](int index) {
		if (index < 0 || index >= size()) {
			cerr << "Subscript out of range" << endl;
			return 0;
		} else {
			return elems[index];
		}
	}

	/// \brief inserts element at index
	void insertAt(const Element &elem, int index) {
		if (index < 0 || index >= size()) {
			cerr << "Subscript out of range" << endl;
		} else {
			elems.insert(elems.begin() + index, elem);
		}
	}

	/// \brief append element
	void append(const Element &elem) {
		elems.push_back(elem);
	}

	/// \brief removes element at index
	void removeAt(int index) {
		if (index < 0 || index >= size()) {
			cerr << "Subscript out of range" << endl;
		} else {
			elems.erase(elems.begin() + index);
		}
	}
};

#endif				/* !LIBS_LIST_H */
