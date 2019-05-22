## For students: change this path to the root of your code
INCLUDEROOT = include

## If you use OS X, then use CC = g++ , instead of CC = g++-4.8
CC = g++
CXX = $(CC)

USER_DEFINED=

# Comment the following line to disable command line interface (CLI).
CPPFLAGS = -Wall -I$(INCLUDEROOT) -std=c++11 -g $(USER_DEFINED)
LFLAGS   = -Wall -I$(INCLUDEROOT) -lm

SRCDIR   = src
OBJDIR   = obj
BINDIR   = bin
TESTDIR  = test

SOURCES  := $(wildcard $(SRCDIR)/*.cpp)
INCLUDES := $(wildcard $(INCLUDEROOT)/*.h)
OBJECTS  := $(SOURCES:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)

rm = rm -rf
