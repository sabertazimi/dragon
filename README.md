# Hust Compiler Lab - Dragon Language Compiler

A toy compiler for Dragon language

[![Author](https://img.shields.io/badge/author-sabertazimi-lightgrey.svg)](https://github.com/sabertazimi)
[![Build Status](https://travis-ci.com/sabertazimi/dragon.svg?token=q3rvCWEJVuEsNxEomDdy&branch=master)](https://travis-ci.com/sabertazimi/dragon)
[![MIT](https://img.shields.io/badge/license-mit-brightgreen.svg)](https://raw.githubusercontent.com/sabertazimi/dragon/master/LICENSE)

## Installation

```sh
$ sudo apt install flex bison
```

## Lex Notes

### Built-in Variables/Macros/Functions

```lex
yytext   char * 当前匹配的字符串
yyleng   int     当前匹配的字符串长度
yyin     FILE * lex当前的解析文件，默认为标准输出
yyout    FILE * lex解析后的输出文件，默认为标准输入
yylineno int     当前的行数信息
yywrap   When the end of the file is reached the return value of yywrap() is checked.If it is non-zero, scanning terminates and if it is 0 scanning continues with next input file.
```

## Yacc Notes

### Flags

*   -d: 产生头文件 
*   -v: 产生分析表(.output)
*   %defines: 产生头文件
*   %error-verbose

### Shift/Reduce Conflicts

可以通过指定优先级与结合性在一定程度上消除 S/R 冲突

```yacc
%left '+' '-'
%left '*' '/'
%left NEG

expr: expr '-' expr
    | '-' expr %prec NEG
    ;
```

## Labs

### AST

*   Print function: Print(recursion, whitespace+4)

## BUGs

### yylloc not decalared in .l

add

```yacc
%locations
```

to .y file

## License

MIT License Copyright (c) 2016 [sabertazimi](https://github.com/sabertazimi)

## Contact

-   [![Email](https://img.shields.io/badge/mailto-sabertazimi-brightgreen.svg?style=flat-square)](mailto:sabertazimi@gmail.com)
-   [![GitHub](https://img.shields.io/badge/contact-github-000000.svg?style=flat-square)](https://github.com/sabertazimi)
-   [![Twitter](https://img.shields.io/badge/contact-twitter-blue.svg?style=flat-square)](https://twitter.com/sabertazimi)
