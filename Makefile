.PHONY: all compile run check doc clean
.DEFAULT_GOAL = all

## Variables

CXX = g++
CXXFLAGS = -Wall -pedantic -Wno-long-long -O0 -ggdb -std=c++14 -Werror
EXECUTABLE = veselmik
SOURCES := $(wildcard src/*.cpp src/*/*.cpp src/*/*/*.cpp src/*/*/*/*.cpp)
CHECK = valgrind
CHECKFLAGS = --leak-check=full --tool=memcheck

## Tasks

%.o: %.cpp
	@echo "$^ -> $@"
	@$(CXX) $(CXXFLAGS) -c -o $@ -c $<
	@$(CXX) $(CXXFLAGS) -MM -MT $*.o $*.cpp  > $*.d

all: doc compile

compile: $(SOURCES:.cpp=.o)
	@echo "compiling with flags $(CXXFLAGS) "
	@$(CXX) $(CXXFLAGS) $(SOURCES:.cpp=.o) -lncurses -o $(EXECUTABLE)
	@echo "compile finished"

run: compile
	@echo "starting executable"
	@./$(EXECUTABLE) --htmltomd ./examples/htmlexample.txt
	@echo "run finished"

clean:
	@echo "removing object files"
	@rm -f -- src/*.o src/*/*.o src/*/*/*.o src/*/*/*/*.o
	@echo "removing link files"
	@rm -f -- src/*.d src/*/*.d src/*/*/*.d src/*/*/*/*.d
	@echo "removing executable files"
	@rm -f $(EXECUTABLE)
	@echo "removing documentation files"
	@rm -rf -- doc/
	@echo "clean finished"

doc:
	@echo "generating documentation"
	doxygen Doxyfile
	@echo "finished"

check: CXXFLAGS += -g -O2
check: clean compile
	@echo "starting check in $(CHECK) with flags $(CHECKFLAGS)"
	$(CHECK) ./$(EXECUTABLE) $(CHECKFLAGS)
	@echo "CHECK OK"

help:
	@echo "Usage: make [TARGET]"
	@echo
	@echo "TARGETS:"
	@echo "  all       create all outputs generated from source code"
	@echo "  compile   compiles outdated object files and creates the executable"
	@echo "  run       does the 'compile' task and then runs the executable file"
	@echo "  clean     removes all of the compiled files and executable"
	@echo "  doc       generates the project documentation"
	@echo "  check     does a clean compilation and runs check tool"
	@echo "  help      print this message"

## Inlude D files

-include $(SOURCES:.cpp=.d)