/*!
 * \file AstPrinter.cc
 * \brief
 *
 * \author sabertazimi, <sabertazimi@gmail.com>
 * \version 1.0
 * \date 2016
 * \license MIT
 */

#include <cstdarg>
#include <iostream>
#include <fstream>
#include "AstPrinter.h"

using namespace std;

class AstPrinter {
public:
    int indent;
    int step;
    char buf[1000];
    ostream *out;
    ofstream fout;

    AstPrinter(void) {
        indent = 0;
        step = 2;
        out = &cout;
    }

    AstPrinter(const char *outfile) {
        indent = 0;
        step = 2;
        fout.open(outfile);
        out = &fout;
    }

	void incIndent() {
        indent += step;
	}

	void decIndent() {
        indent -= step;
	}

    void print(const char *fmt, ...) {
        for (int i = 0; i < indent; i++) {
            *out << " ";
        }

        // output
        va_list args;
        va_start(args, fmt);
        vsnprintf(buf, 1000, fmt, args);
        va_end(args);
        *out << buf << endl;
    }
};

