#
# Makefile
# sabertazimi, 2016-08-10 23:12
#

PROG=decaf

CC=gcc
CC_FLAG=-Wall -std=c99
LEX=flex
LEX_FLAG=
YACC=bison
YACC_FLAG=-dv

RM=rm -fr
MKDIR=mkdir -p
MV=mv

SRC_PATH=src
BIN_PATH=bin
TEST_PATH=test

all:
	make yacc
	make lex
	make build
	make clean
	$(MKDIR) $(BIN_PATH)
	$(MV) $(SRC_PATH)/$(PROG) $(BIN_PATH)/$(PROG)
	@echo
	@echo 'Build Success!'

.PHONY = build lex yacc clean run spec

build:
	$(CC) $(CC_FLAG) $(SRC_PATH)/$(PROG).tab.c $(SRC_PATH)/lex.yy.c -o $(SRC_PATH)/$(PROG)

lex:
	$(LEX) $(LEX_FLAG) -o $(SRC_PATH)/lex.yy.c $(SRC_PATH)/$(PROG).l

yacc:
	$(YACC) $(YACC_FLAG) -o $(SRC_PATH)/$(PROG).tab.c $(SRC_PATH)/$(PROG).y

clean:
	$(RM) $(SRC_PATH)/$(PROG).tab.[ch] $(SRC_PATH)/$(PROG).output $(SRC_PATH)/lex.yy.c 

run:
	./$(BIN_PATH)/$(PROG)

spec:
	./$(BIN_PATH)/$(PROG) $(TEST_PATH)/lex1.decaf

# vim:ft=make
#
