#
# Makefile
# sabertazimi, 2016-08-10 23:12
#

# program name
PROG=dragon

# tools and their flags
CC=gcc
CFLAGS=-Wall -Wextra -std=gnu99 -O2 -g $(addprefix -I, $(INCLUDE_PATH))
LEX=flex
LFLAGS=
YACC=bison
YFLAGS=-dv
GDB=gdb
GFLAGS= -q -x tools/gdbinit
RM=rm -fr
MKDIR=mkdir -p
MV=mv
ZIP=zip

# paths
SRC_PATH=src
OBJ_PATH=obj
BIN_PATH=bin
TEST_PATH=test
TOOLS_PATH=tools
INCLUDE_PATH=src/libs 		\
			 src/errors 	\
			 src/ast 		\
			 src/semantic 	\
			 src/spec

# test enable flags
LEX_TEST=0
SYNTAX_TEST=0
AST_TEST=0
SEMA_TEST=1

# objects
RAW_SRCS=$(shell find $(SRC_PATH) -name "*.c" -print)
RAW_OBJS=$(patsubst %.c, %.o, $(RAW_SRCS))
OBJS=$(SRC_PATH)/parser.o $(SRC_PATH)/scanner.o $(RAW_OBJS)

# rules
%.o: %.c
	@echo '>>>' Compiling C Source Files $< ... '<<<'
	$(CC) $(CFLAGS) -o $@ -c $<
	$(MV) $@ $(OBJ_PATH)/$(notdir $@)
	@echo '>>>' Compile $< Success! '<<<'

%.c: %.l
	@echo '>>>' Compiling Lex Source Files $< ... '<<<'
	$(MKDIR) $(OBJ_PATH)
	$(LEX) $(LFLAGS) -o $(@:%.o=%.d) $<
	@echo '>>>' Compile $< Success! '<<<'

%.c: %.y
	@echo '>>>' Compiling Yacc Source Files $< ... '<<<'
	$(MKDIR) $(OBJ_PATH)
	$(YACC) $(YFLAGS) -o $(@:%.o=%.d) $<
	@echo '>>>' Compile $< Success! '<<<'

all: $(PROG)

# dependencies
$(PROG): $(OBJS)
	$(CC) $(CFLAGS) -o $(SRC_PATH)/$(PROG) $(patsubst %.o, $(OBJ_PATH)/%.o, $(notdir $(RAW_OBJS)))
	make release
	make clean
	@echo
	@echo '>>>' Build Success! '<<<'

.PHONY = clean release run count spec debug

clean:
	$(RM) $(OBJ_PATH) $(OBJS)
	$(RM) $(SRC_PATH)/parser.h $(SRC_PATH)/parser.c  $(SRC_PATH)/scanner.c
	$(RM) $(SRC_PATH)/parser.output $(SRC_PATH)/$(PROG)
	$(RM) core
# $(RM) .gdb_history

release:
	$(MKDIR) $(BIN_PATH)
	$(MV) $(SRC_PATH)/parser.output  $(BIN_PATH)/parser.output
	$(MV) $(SRC_PATH)/$(PROG) $(BIN_PATH)/$(PROG)

run:
	./$(BIN_PATH)/$(PROG)

count:
	./$(TOOLS_PATH)/line_counter

spec:
ifeq ($(LEX_TEST), 1)
	$(foreach filename, $(shell find $(TEST_PATH) -name "lex_*"), echo "\n>>> Lex test for" $(filename) "<<<\n" && ./$(BIN_PATH)/$(PROG) $(filename);)
	@echo
	@echo '>>>' Lex Test Passed! '<<<'
	@echo
endif
ifeq ($(SYNTAX_TEST), 1)
	$(foreach filename, $(shell find $(TEST_PATH) -name "errors_*"), echo "\n>>> Syntax error report test for" $(filename) "<<<\n" && ./$(BIN_PATH)/$(PROG) $(filename);)
	@echo
	@echo '>>>' Syntax Error Report Test Passed! '<<<'
	@echo
endif
ifeq ($(AST_TEST), 1)
	$(foreach filename, $(shell find $(TEST_PATH) -name "ast_*"), echo "\n>>> Ast test for" $(filename) "<<<\n" && ./$(BIN_PATH)/$(PROG) $(filename);)
	@echo
	@echo '>>>' Ast Test Passed! '<<<'
	@echo
endif
ifeq ($(SEMA_TEST), 1)
	$(foreach filename, $(shell find $(TEST_PATH) -name "sema_*"), echo "\n>>> Semantic test for" $(filename) "<<<\n" && ./$(BIN_PATH)/$(PROG) $(filename);)
	@echo
	@echo '>>>' Semantic Test Passed! '<<<'
	@echo
endif



debug:
	$(GDB) $(GFLAGS) $(BIN_PATH)/$(PROG) core
# $(RM) .gdb_history

# vim:ft=make
#
