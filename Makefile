NAME = compiler
SHELL = sh
CC = gcc
CXX = g++
REMOVE = rm -f
REMOVEDIR = rm -rf

DEPDIR = .dep
DOCDIR = doc
TESTDIR = tests

SRC =	main.cpp \
		messages.cpp \
		lexer.cpp \
		token.cpp \
		symbol.cpp \
		symbol_table.cpp \
		syntax_tree.cpp \
		parser.cpp \
		semantic_analyzer.cpp \
		code_generator.cpp \
		gforth_code_generator.cpp \

DEBUG = -g
OPTIMIZATION = -O3  
CSTANDARD = -std=c++0x
INCLUDEDIRS = 
OBJDIR = obj
RUNFLAGS = 

CFLAGS =	$(INCLUDEDIRS) \
			-Wall \
			-Wextra \
			-Wmissing-declarations \
			$(CSTANDARD) \
			$(OPTIMIZATION) \

LDFLAGS = 

# Compiler flags to generate dependency files.
GENDEPFLAGS = -MMD -MP -MF $(DEPDIR)/$(@F).d

# Combine all necessary flags and optional flags.
ALL_CFLAGS = $(CFLAGS) $(GENDEPFLAGS)

OBJ = $(SRC:%.cpp=$(OBJDIR)/%.o)

all: $(NAME)
default: $(NAME)

# Link object files to executable
$(NAME): $(OBJ)
	@echo 'LD: $@'
	@$(CXX) -o $@ $(ALL_CFLAGS) $^ $(LDFLAGS)

stutest.out: $(NAME)
	@make -C $(TESTDIR) > /dev/null
	@-make test | grep -v make > stutest.out

proftest.out: $(NAME)
	cat $(PROFTEST)
	$(NAME) $(PROFTEST) > proftest.out
	cat proftest.out

# Compile: create object files from C++ source files.
$(OBJDIR)/%.o : %.cpp
	@echo 'CC: $<'
	@$(CXX) -c $(ALL_CFLAGS) $< -o $@ 

doc:
	doxygen
	make -C $(DOCDIR)/latex

test: $(NAME) 
	make -C $(TESTDIR)
	python $(TESTDIR)/run-tests.py

clean:
	-make -C $(TESTDIR) clean
	$(REMOVE) stutest.out
	$(REMOVE) $(NAME)
	$(REMOVE) $(SRC:%.cpp=$(OBJDIR)/%.o)
	$(REMOVE) $(SRC:.cpp=.d)
	$(REMOVEDIR) $(DEPDIR)
	$(REMOVEDIR) $(OBJDIR)
	$(REMOVEDIR) $(DOCDIR)

distclean: clean
	make -C $(TESTDIR) distclean

# Create object files directory
$(shell mkdir $(OBJDIR) 2>/dev/null)

# Include the dependency files.
-include $(shell mkdir $(DEPDIR) 2>/dev/null) $(wildcard $(DEPDIR)/*)

# Listing of phony targets.
.PHONY : clean doc stutest.out

