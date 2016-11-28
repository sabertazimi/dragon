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

#endif /* !LOCATION_H */
