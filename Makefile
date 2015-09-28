ASAN=-fsanitize=thread -fno-omit-frame-pointer
INCLUDE=-Iinclude
CXXFLAGS=$(INCLUDE) -g -Wall -Wextra -std=c++14 -O0 -pthread $(ASAN)
LIB=-lncurses -lpthread $(ASAN)

CXX=clang++
EXECDIR=./bin
OBJDIR=./obj
PROGRAM=kuratko

SRC=$(wildcard src/*.cpp src/**/*.cpp)
OBJ=$(patsubst src/%.cpp, $(OBJDIR)/%.o, $(SRC))

.PHONY: $(PROGRAM)

all: run

$(OBJDIR)/%.o: src/%.cpp
	mkdir -p $(OBJDIR)/core
	mkdir -p $(OBJDIR)/gui

	$(CXX) $(CXXFLAGS) -c $< -o $@

$(PROGRAM): $(OBJ)
	$(CXX) $(LIB) $(OBJ) -o $(EXECDIR)/$(PROGRAM)

run: $(PROGRAM)
	$(EXECDIR)/$(PROGRAM) 2>tmp/asan.txt

valgrind: $(PROGRAM)
	valgrind --log-file=tmp/valgrind.txt $(EXECDIR)/$(PROGRAM)

clean:
	rm -rf -- $(OBJDIR)/*.o $(EXECDIR)/$(PROGRAM) tmp/*
