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

/// \brief to store location information
typedef struct yyltype {
  int first_line;
  int first_column;
  int last_line;
  int last_column;
} yyltype;

#define YYLTYPE yyltype

extern struct yyltype yylloc;

/// \brief duplicate a yyltype node
yyltype *locdup(yyltype *loc) {
    yyltype * p = (yyltype *)malloc(sizeof(yyltype));
    p->first_line = loc->first_line;
    p->first_column = loc->first_column;
    p->last_line = loc->last_line;
    p->last_column = loc->last_column;
    return p;
}





#endif /* !LOCATION_H */
