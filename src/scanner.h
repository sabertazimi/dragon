/*
 * scanner.h
 * Copyright (C) 2016 sabertazimi <sabertazimi@gmail.com>
 *
 * Distributed under terms of the MIT license.
 */

#ifndef SCANNER_H
#define SCANNER_H

/*
 * @brief: to store location information
 */
typedef struct yyltype {
  int first_line;
  int first_column;
  int last_line;
  int last_column;
} yyltype;

#define YYLTYPE yyltype

extern struct yyltype yylloc;

#endif /* !SCANNER_H */
