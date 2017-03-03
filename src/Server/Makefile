# Authors : Rahul Rathore, Anmol Sood, Kartikay Garg
# Makefile for Assignment 1 : COP290 2014-2015
# Default Compiler g++
CC := g++
SRCDIR := src
BUILDDIR := build
TARGET := bin/server

# Setting compile flags for gcc:
CFLAGS := -g -w -std=c++11
CPPFLAGS := -DDEBUG

# The LDFLAGS variable sets flags for linker
LIB := -L/usr/lib -lssl -lcrypto -lsqlite3

# Macros for first target (execute)
SRCEXT := cpp
SOURCES := $(shell find $(SRCDIR) -type f -name *.$(SRCEXT))
OBJECTS := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.$(SRCEXT)=.o))
INC := -I include

#Caution : TAB Necessary for Specifying Dependencies Relationship
# Target : Dependencies

all : $(OBJECTS)
	@echo " $(CC) $^ -o $(TARGET) $(LIB)"; $(CC) $(CFLAGS) $^ -o $(TARGET) $(LIB)

server : $(OBJECTS)
	@echo " $(CC) $^ -o $(TARGET) $(LIB)"; $(CC) $(CFLAGS) $^ -o $(TARGET) $(LIB)
	./$(TARGET) $(port)

DEBUG :
	@echo " $(CC) $(CFLAGS) $(CPPFLAGS) $(INC) $(SOURCES) $^ -o $(TARGET) $(LIB)"; $(CC) $(CFLAGS) $(CPPFLAGS) $(INC) $(SOURCES) $^ -o $(TARGET) $(LIB)
	./$(TARGET) $(port)

$(BUILDDIR)/%.o: $(SRCDIR)/%.$(SRCEXT)
	@mkdir -p $(BUILDDIR)
	@echo " $(CC) $(CFLAGS) $(INC) -c -o $@ $<"; $(CC) $(CFLAGS) $(INC) -c -o $@ $<

clean:
	@echo " Cleaning...";
	@echo " $(RM) -r $(BUILDDIR) $(TARGET)"; $(RM) -r $(BUILDDIR) $(TARGET)

# Phony means not a "real" target, it doesn't build anything
# The phony target "clean" is used to remove all compiled object files.
.PHONY: clean
