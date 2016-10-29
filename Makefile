#
# Makefile
# sabertazimi, 2016-08-10 23:12
#

# program name
PROG=dragon

# tools and their flags
CC=gcc
CC_FLAG=-Wall -Werror -std=gnu99 -I$(INCLUDE_PATH) -O2
LEX=flex
LEX_FLAG=
YACC=bison
YACC_FLAG=-dv
RM=rm -fr
MKDIR=mkdir -p
MV=mv

# paths
SRC_PATH=src
OBJ_PATH=obj
BIN_PATH=bin
TEST_PATH=test
INCLUDE_PATH=src/libs 	\
			 src/errors

# objects
RAW_SRCS=$(shell find $(SRC_PATH) -name "*.c" -print)
RAW_OBJS=$(patsubst %.c, %.o, $(RAW_SRCS))
OBJS=$(RAW_OBJS) $(SRC_PATH)/scanner.o $(SRC_PATH)/parser.o

# rules
%.c: %.y
	$(YACC) $(YACC_FLAG) -o $(@:%.o=%.d) $<

%.c: %.l
	$(LEX) $(LEX_FLAG) -o $(@:%.o=%.d) $<

all: $(PROG)

# dependencies
$(PROG): $(OBJS)
	$(CC) $(CC_FLAG) -o $(SRC_PATH)/$(PROG) $(patsubst %.o, $(OBJ_PATH)/%.o, $(notdir $(OBJS)))
	make clean
	make release
	@echo
	@echo 'Build Success!'


.c.o:
	@echo Compiling C Source Files $< ...
	$(MKDIR) $(OBJ_PATH)
	$(CC) $(CC_FLAGS) -o $@ $<
	$(MV) $@ $(OBJ_PATH)/$(notdir $@)

parser.c: parser.y

scanner.c: scanner.l

.PHONY = run spec count

clean:
	$(RM) $(OBJ_PATH)/*.o $(SRC_PATH)/parser.h $(SRC_PATH)/parser.c $(SRC_PATH)/parser.output $(SRC_PATH)/scanner.c 

release:
	$(MKDIR) $(BIN_PATH)
	$(MV) $(SRC_PATH)/$(PROG) $(BIN_PATH)/$(PROG)

run:
	./$(BIN_PATH)/$(PROG)

spec:
	$(foreach filename, $(shell find $(TEST_PAH) -name "*.dg"), echo "\nSpec test for" $(filename) "\n" && ./$(BIN_PATH)/$(PROG) $(filename);)
	@echo
	@echo 'Spec Test Passed!'

count:
	$(shell find src -name "*.[chly]" | xargs cat | grep -v ^$ | wc -l)

# vim:ft=make
#
