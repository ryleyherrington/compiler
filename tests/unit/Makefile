NAME = unit_tests
SHELL = sh
CC = gcc
CXX = g++
REMOVE = rm -f
REMOVEDIR = rm -rf

DEPDIR = .dep
SRCDIR = ../..

SRC =	main.cpp \
		random.cpp \
		token_tests.cpp \
		symbol_table_tests.cpp \
		syntax_tree_tests.cpp \
		$(SRCDIR)/messages.cpp \
		$(SRCDIR)/lexer.cpp \
		$(SRCDIR)/token.cpp \
		$(SRCDIR)/symbol.cpp \
		$(SRCDIR)/symbol_table.cpp \
		$(SRCDIR)/syntax_tree.cpp \

DEBUG = -g
OPTIMIZATION = -O3
CSTANDARD = -std=c++0x
INCLUDEDIRS = -I../gtest/include -I$(SRCDIR)
OBJDIR = obj

CFLAGS =	$(INCLUDEDIRS) \
			-Wall \
			-Wextra \
			-Wmissing-declarations \
			$(CSTANDARD) \
			$(OPTIMIZATION) \

LDFLAGS =	-L../gtest/lib/ -lgtest -lpthread

# Compiler flags to generate dependency files.
GENDEPFLAGS = -MMD -MP -MF $(DEPDIR)/$(@F).d

# Combine all necessary flags and optional flags.
ALL_CFLAGS = $(CFLAGS) $(GENDEPFLAGS)

OBJ = $(SRC:%.cpp=$(OBJDIR)/%.o)

all: $(NAME)
default: all

test: $(NAME)
	./unit_tests

# Link object files to executable
$(NAME): $(OBJ) ../gtest/lib/libgtest.a
	@echo 'LD: $@'
	@$(CXX) -o $@ $(ALL_CFLAGS) $^ $(LDFLAGS)

# Compile: create object files from C++ source files.
$(OBJDIR)/%.o : %.cpp
	@echo 'CC: $<'
	@$(CXX) -c $(ALL_CFLAGS) $< -o $@ 

../gtest/lib/libgtest.a:
	make -C .. gtest/lib/libgtest.a

clean:
	$(REMOVE) $(NAME)
	-$(REMOVE) *.pyc
	$(REMOVE) $(SRC:%.cpp=$(OBJDIR)/%.o)
	$(REMOVE) $(SRC:.cpp=.d)
	$(REMOVEDIR) $(DEPDIR)
	$(REMOVEDIR) $(OBJDIR)
		

# Create object files directory
$(shell mkdir $(OBJDIR) 2>/dev/null)

# Include the dependency files.
-include $(shell mkdir $(DEPDIR) 2>/dev/null) $(wildcard $(DEPDIR)/*)

# Listing of phony targets.
.PHONY : clean

