
CC := clang++

TARGET := bin/raytracer
SOURCES := $(shell find src -type f -name *.cpp)
OBJECTS := $(patsubst src/%,build/%,$(SOURCES:.cpp=.o))
DEPENDS := ${OBJECTS:.o=.d}
CFLAGS := -std=c++14 -fopenmp  -MMD -O0 -g -Wall -DLOG -fsanitize=undefined
LIB := -pthread
INC := -I include

$(TARGET): $(OBJECTS)
	@echo "Linking..."
	@echo "$(CC) $(CFLAGS) $^ -o $(TARGET) $(LIB)"; $(CC) $(CFLAGS) $^ -o $(TARGET) $(LIB)

-include ${DEPENDS}

build/%.o: src/%.cpp
	@mkdir -p build build/objects logs
	@echo "$(CC) $(CFLAGS) $(INC) -c -o $@ $<"; $(CC) $(CFLAGS) $(INC) -c -o $@ $<

clean:
	@echo "Cleaning...";
	find build ! -type d -delete
	$(RM) $(TARGET) logs/*

tester: $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS:build/main.o=) test/tester.cpp $(INC) $(LIB) -o bin/tester

check:
	@echo " Checking..."
	@cppcheck -q --report-progress -j 8 --check-library --force -I /usr/include -I include --enable=warning --enable=style --enable=performance --std=c++11 --language=c++ --suppress=missingInclude --inconclusive --suppress=information src/*

wc:
	@find . -name '*.cpp' -o -name '*.h' | xargs wc

todo:
	@git grep -EIn "TODO|FIXME|XXX" | egrep "^(src|test|include)" | cat

.PHONY: clean wc todo
