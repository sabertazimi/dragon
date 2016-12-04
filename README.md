# Hust Compiler Lab - Dragon Language Compiler

A toy compiler for Dragon language

[![Author](https://img.shields.io/badge/author-sabertazimi-lightgrey.svg)](https://github.com/sabertazimi)
[![Build Status](https://travis-ci.com/sabertazimi/dragon.svg?token=q3rvCWEJVuEsNxEomDdy&branch=master)](https://travis-ci.com/sabertazimi/dragon)
[![MIT](https://img.shields.io/badge/license-mit-brightgreen.svg)](https://raw.githubusercontent.com/sabertazimi/dragon/master/LICENSE)

## Installation

```sh
$ sudo apt install flex bison
```

## Frame

### Ast node

Program/ClassDef/FuncDef/Block has a scope:

*   Program/Block with Scope member
*   ClassDef/Funcdef with Symbol member(symbol->definedIn)

VarDef has a symbol member

Lvalue(Ident/Ref/Indexed) has symbol member

### Scope

Scope has Symbol member

### Symbol(information center)

*   symbol has Type member, Scope member(definedIn/associatedScope), Tac member
*   order of class: depth of inheriting tree

### Tac

*   new -> static constructor(direct funtion call)
*   libs -> static function(direct function call)
*   methods -> search vtable to get method reference, indirect function call

## Built-in Variables/Macros/Functions

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

### Error Recovery

只需将规则中所有终结符依次替换为 error 即可

## Labs

### AST

*   Print function: Print(recursion, whitespace+4)

## BUGs

### string + int

```cpp
int a = 1;
"_T" + 1;
```

以上操作, operator+(string, int), 不起任何作用. 会产生一个空 string:

导致 IR 生成大面积错误, 导致 TAC 打印大面积错误

### Flags

*   LEX_DEBUG in scanner.ll: print tokens
*   AST_DEBUG in dragon.cc: print ast tree
*   SEMA_DEBUG in dragon.cc: print scopes and symbols

### Debug Tips

```sh
$ ulimit -c 0
```

```sh
$ ulimit -c unlimited
```

可使得程序产生段错误时生成 core 文件, 使用 gdb 打开 core 文件可获得段错误的详细信息

```sh
$ gdb prog core
```

### yylloc not decalared in .l

add

```yacc
%locations
```

to .y file

### circle defination dependencies

solution: pre-defination(without implement)

### re-defination variable in switch/case statement

solution: block scope

### core dump/segment fault

对于文法中存在的所有 NULL 结点, 在对其进行操作(除创建外)时必须进行空检查

*   ifstmt -> body
*   simplestmt
*   retstmt
*   formals/actuals list: void -> Null

## Change Language

*   实验刚开始时自信满满地用 C 语言进行编译器的编写, 但现实狠狠地打了脸. 从 Lab 2 开始, 代码变得杂乱无序(特别是对于语法树结点类型的判断), 每次遍历语法树都要重写许多代码
*   虽然实现了模块的解耦, 但 Lab 2 中的代码依赖于未抽象的语法树结点, 导致在进行语义分析时, 特别是建立 scope 时, 还得修改语法树定义以及结点创建函数, 浪费大量精力
*   进入 Lab 3 后, 发现用 void * 来支持泛型特性的数据结构(list 与 stack), 在很多情况下需要 enum kind 来辅助进行类型判断, 再对 void * 进行强制类型转化, 使用起来十分地不方便
*   而 泛型 list 与 泛型 stack 已经满足不了需求, 但又没有太多地时间去实现与测试支持泛型特性的 map/set 等复杂数据结构

综合以上原因, 为了使得后面的编码变得更加地顺利, 提高编码的效率, 从 Lab 3 开始将编写语言由 C 切换至 C++

## Challenges

*   inheritance
*   OO(3 points)
*   call/field ref/ident ref(receiver.member)(member)

## Reference

*   Text Book
*   Lab Book
*   [Flex/Bison with C++](http://www.doc88.com/p-2989810281943.html)
*   [Language Implementation Patterns](https://book.douban.com/subject/10482195)
*   [TsingHua Decaf](https://github.com/Silver-Shen/decaf_PA3])
*   [CS143 Decaf](https://github.com/davidzchen/decaf)
*   CSAPP(x86 IR Generation)

## License

MIT License Copyright (c) 2016 [sabertazimi](https://github.com/sabertazimi)

## Contact

-   [![Email](https://img.shields.io/badge/mailto-sabertazimi-brightgreen.svg?style=flat-square)](mailto:sabertazimi@gmail.com)
-   [![GitHub](https://img.shields.io/badge/contact-github-000000.svg?style=flat-square)](https://github.com/sabertazimi)
-   [![Twitter](https://img.shields.io/badge/contact-twitter-blue.svg?style=flat-square)](https://twitter.com/sabertazimi)
