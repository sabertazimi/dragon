#
# Makefile
# sabertazimi, 2016-08-10 23:12
#

PROG=dragon

CC=gcc
CC_FLAG=-Wall -Werror -Wno-format-security -std=gnu99 -I$(INCLUDE_PATH) -O2
# CC_FLAG=-Wall -Wextra -std=c99 -O2
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
INCLUDE_PATH=src/libs

all:
	make yacc
	make lex
	make build
	make clean
	make release
	@echo
	@echo 'Build Success!'

.PHONY = build lex yacc clean release run spec count

build:
	$(CC) $(CC_FLAG) $(SRC_PATH)/dragon.c $(SRC_PATH)/$(PROG).tab.c $(SRC_PATH)/lex.yy.c -o $(SRC_PATH)/$(PROG)

lex:
	$(LEX) $(LEX_FLAG) -o $(SRC_PATH)/lex.yy.c $(SRC_PATH)/$(PROG).l

yacc:
	$(YACC) $(YACC_FLAG) -o $(SRC_PATH)/$(PROG).tab.c $(SRC_PATH)/$(PROG).y

clean:
	$(RM) $(SRC_PATH)/$(PROG).tab.[ch] $(SRC_PATH)/$(PROG).output $(SRC_PATH)/lex.yy.c 

release:
	$(MKDIR) $(BIN_PATH)
	$(MV) $(SRC_PATH)/$(PROG) $(BIN_PATH)/$(PROG)

run:
	./$(BIN_PATH)/$(PROG)

spec:
	$(foreach filename, $(shell find $(TEST_PAH) -name "lex*"), ./$(BIN_PATH)/$(PROG) $(filename);)

count:
	$(shell find src -name "*.[chly]" | xargs cat | grep -v ^$ | wc -l)

# vim:ft=make
#
