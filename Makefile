#
# Makefile
# sabertazimi, 2016-08-10 23:12
#

PROG=calculate
CC=gcc
CC_FLAG=-Wall -std=c99
FLEX=lex
FLEX_FLAG=
YACC=bison
YACC_FLAG=-dv
RM=rm -fr
MKDIR=mkdir -p

all:
	make purge
	make yacc
	make flex
	$(CC) $(CC_FLAG) $(PROG).tab.c lex.yy.c -o $(PROG)
	make clean

.PHONY = flex yacc clean purge run

flex:
	$(FLEX) $(FLEX_FLAG) $(PROG).l

yacc:
	$(YACC) $(YACC_FLAG) $(PROG).y

clean:
	$(RM) $(PROG).tab.[ch] $(PROG).output lex.yy.c 

purge:
	make clean
	$(RM) $(PROG)

run:
	./$(PROG)

# vim:ft=make
#
