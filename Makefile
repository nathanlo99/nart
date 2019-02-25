
CC := clang++

TARGET := bin/raytracer
SOURCES := $(shell find src -type f -name *.cpp)
OBJECTS := $(patsubst src/%,build/%,$(SOURCES:.cpp=.o))
DEPENDS := ${OBJECTS:.o=.d}
FASTFLAGS := -flto -fwhole-program-vtables -Ofast
DEBUGFLAGS := -fsanitize=undefined,nullability -fno-omit-frame-pointer -O2 -g -Wall -Wextra -pedantic -Wconversion -Wunreachable-code -Wuninitialized -Wold-style-cast -Wno-error=unused-parameter -Wno-error=unused-variable -Weffc++ -Wfloat-equal -Wmost

CFLAGS := -std=c++17 -fopenmp -MMD -DLOG $(FASTFLAGS)

LIB := -lbenchmark -pthread -lc++abi
INC := -I include

$(TARGET): $(OBJECTS)
	@echo "Linking..."
	$(CC) $(CFLAGS) $^ -o $(TARGET) $(LIB)

-include ${DEPENDS}

build/%.o: src/%.cpp
	@mkdir -p build build/objects logs
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<

clean:
	@echo "Cleaning...";
	find build ! -type d -delete
	$(RM) $(TARGET) logs/*

tester: $(OBJECTS:build/main.o=)
	$(CC) $(CFLAGS) $(OBJECTS:build/main.o=) test/tester.cpp $(INC) $(LIB) -o bin/tester

check:
	@echo " Checking..."
	@cppcheck -q --report-progress -j 8 --check-library --force -I /usr/include -I include --enable=warning --enable=style --enable=performance --std=c++11 --language=c++ --suppress=missingInclude --inconclusive --suppress=information src/*

wc:
	@find . -name '*.cpp' -o -name '*.h' | xargs wc

todo:
	@git grep -EIn "TODO|FIXME|XXX" | egrep "^(src|test|include)" | cat

benchmark: $(OBJECTS:build/main.o=)
	@clang++ $(CFLAGS) -c test/benchmark.cpp -Iinclude -o build/benchmark.o
	@clang++ $(CFLAGS) $(OBJECTS:build/main.o=build/benchmark.o) -o bin/benchmark $(LIB)
	bin/benchmark

profile: $(TARGET)
	@sudo perf record -g $(TARGET)
	@sudo perf report -g 'graph,0.1,caller'

.PHONY: clean wc todo benchmark
