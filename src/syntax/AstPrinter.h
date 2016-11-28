/*!
 * \file AstPrinter.h
 * \brief
 *
 * \author sabertazimi, <sabertazimi@gmail.com>
 * \version 1.0
 * \date 2016
 * \license MIT
 */

#ifndef SYNTAX_ASTPRINTER_H
#define SYNTAX_ASTPRINTER_H

#include <cstdarg>
#include <iostream>
#include <fstream>

using namespace std;

class AstPrinter {
public:
    int indent;     ///< current indent distance
    int step;       ///< increase/decrease step
    char buf[1000]; ///< string buffer
    ostream *out;   ///< outout stream
    ofstream fout;  ///< file stream

    /// \brief constructor
    AstPrinter(void);

    /// \brief constructor
    AstPrinter(const char *outfile);

    /// \brief increase indent distance
	void incIndent(void);

    /// \brief decrease indent distance
	void decIndent(void);

    /// \brief write fmt str to outfile
    void print(const char *fmt, ...);
};

#endif /* !SYNTAX_ASTPRINTER_H */
