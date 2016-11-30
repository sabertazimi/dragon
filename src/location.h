/*!
 * \file location.h
 * \brief
 *
 * \author sabertazimi, <sabertazimi@gmail.com>
 * \version 1.0
 * \date 2016
 * \license MIT
 */

#ifndef LOCATION_H
#define LOCATION_H

#include <stdlib.h>

/// \brief store location information
typedef struct yyltype {
    int first_line;
    int first_column;
    int last_line;
    int last_column;
} yyltype;

#define YYLTYPE yyltype

extern struct yyltype yylloc;

/// \brief duplicate a yyltype node
/// \param loc location information
/// \return duplication of loc
yyltype *locdup(yyltype *loc);

/// \brief compare two location
/// \param l location information
/// \param r location information
/// \return comparation bool value(l > r ? 1 : l == r ? 0 : -1)
int loccmp(yyltype *l, yyltype *r);

#endif /* !LOCATION_H */
