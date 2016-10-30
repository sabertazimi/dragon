#
# Makefile
# sabertazimi, 2016-08-10 23:12
#

# program name
PROG=dragon

# tools and their flags
CC=gcc
CFLAGS=-Wall -Werror -std=gnu99 -O2 $(addprefix -I, $(INCLUDE_PATH))
LEX=flex
LFLAGS=
YACC=bison
YFLAGS=-dv
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
OBJS=$(SRC_PATH)/parser.o $(SRC_PATH)/scanner.o $(RAW_OBJS)

# rules
%.o: %.c
	@echo Compiling C Source Files $< ...
	$(CC) $(CFLAGS) -o $@ -c $<
	$(MV) $@ $(OBJ_PATH)/$(notdir $@)
	@echo Compile $< Success!

%.c: %.l
	@echo Compiling Lex Source Files $< ...
	$(MKDIR) $(OBJ_PATH)
	$(LEX) $(LFLAGS) -o $(@:%.o=%.d) $<
	@echo Compile $< Success!

%.c: %.y
	@echo Compiling Yacc Source Files $< ...
	$(MKDIR) $(OBJ_PATH)
	$(YACC) $(YFLAGS) -o $(@:%.o=%.d) $<
	@echo Compile $< Success!

all: $(PROG)

# dependencies
$(PROG): $(OBJS)
	$(CC) $(CFLAGS) -o $(SRC_PATH)/$(PROG) $(patsubst %.o, $(OBJ_PATH)/%.o, $(notdir $(RAW_OBJS)))
	make clean
	make release
	@echo
	@echo 'Build Success!'

.PHONY = clean release run spec count

clean:
	$(RM) $(OBJ_PATH) $(OBJS)
	$(RM) $(SRC_PATH)/parser.h $(SRC_PATH)/parser.c $(SRC_PATH)/scanner.c

release:
	$(MKDIR) $(BIN_PATH)
	$(MV) $(SRC_PATH)/parser.output  $(BIN_PATH)/parser.output
	$(MV) $(SRC_PATH)/$(PROG) $(BIN_PATH)/$(PROG)

run:
	./$(BIN_PATH)/$(PROG)

spec:
	$(foreach filename, $(shell find $(TEST_PATH) -name "errors_*"), echo "\nSpec test for" $(filename) "\n" && ./$(BIN_PATH)/$(PROG) $(filename);)
	@echo
	@echo 'Spec Test Passed!'

count:
	$(shell find src -name "*.[chly]" | xargs cat | grep -v ^$ | wc -l)

# vim:ft=make
#
