ASAN=-fsanitize=address -fno-omit-frame-pointer
INCLUDE=-Iinclude
CXXFLAGS=$(INCLUDE) -g -Wall -Wextra -std=c++1y -O0 $(ASAN)
LIB=-lncurses $(ASAN)

CXX=clang++
EXECDIR=./bin
OBJDIR=./obj
PROGRAM=kuratko

SRC=$(wildcard src/*.cpp src/*.c)
TEMPOBJ=$(patsubst src/%.cpp, $(OBJDIR)/%.o, $(SRC))
OBJ=$(patsubst stc/%.c, $(OBJDIR)/%.o, $(TEMPOBJ))

.PHONY: $(PROGRAM)

all: run

# TODO - fix clang linker
$(OBJDIR)/%.o: src/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(PROGRAM): $(OBJ)
	$(CXX) $(LIB) $(OBJ) -o $(EXECDIR)/$(PROGRAM)

run: $(PROGRAM)
	$(EXECDIR)/$(PROGRAM) 2>tmp/asan.txt

valgrind: $(PROGRAM)
	valgrind --log-file=tmp/valgrind.txt $(EXECDIR)/$(PROGRAM)

clean:
	rm -f -- $(OBJDIR)/*.o $(EXECDIR)/$(PROGRAM)
