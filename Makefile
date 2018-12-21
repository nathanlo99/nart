
CC := g++

SRCDIR := src
BUILDDIR := build
TARGET := bin/raytracer
LOGS := logs

SRCEXT := cpp
SOURCES := $(shell find $(SRCDIR) -type f -name *.$(SRCEXT))
OBJECTS := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.$(SRCEXT)=.o))
CFLAGS := -std=c++14 -fopenmp  -MMD -Og -g -Wall
LIB := -pthread
INC := -I include

$(TARGET): $(OBJECTS)
	@echo "Linking..."
	@echo "$(CC) $(CFLAGS) $^ -o $(TARGET) $(LIB)"; $(CC) $(CFLAGS) $^ -o $(TARGET) $(LIB)

$(BUILDDIR)/%.o: $(SRCDIR)/%.$(SRCEXT)
	@mkdir -p $(BUILDDIR)
	@echo "$(CC) $(CFLAGS) $(INC) -c -o $@ $<"; $(CC) $(CFLAGS) $(INC) -c -o $@ $<

-include ${DEPENDS}

clean:
	@echo "Cleaning...";
	@echo "$(RM) -r $(BUILDDIR) $(TARGET)"; $(RM) -r $(BUILDDIR) $(TARGET)
	@echo "$(RM) logs/*"; $(RM) logs/*

tester:
	$(CC) $(CFLAGS) test/tester.cpp $(INC) $(LIB) -o bin/tester

wc:
	@find . -name '*.cpp' -o -name '*.h' | xargs wc

todo:
	@git grep -iEI "TODO|FIXME|XXX" | egrep -v "^Makefile" | cat

.PHONY: clean wc todo
