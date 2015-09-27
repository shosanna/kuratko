INCLUDE=-Iinclude
CXXFLAGS=$(INCLUDE) -g -Wall -Wextra -std=c++1y
LIB=-lstdc++ -lncurses

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
	clang++ $(CXXFLAGS) -c $< -o $@

$(PROGRAM): $(OBJ)
	clang++ $(LIB) $(OBJ) -o $(EXECDIR)/$(PROGRAM)

run: $(PROGRAM)
	valgrind --log-file=val.txt $(EXECDIR)/$(PROGRAM)

clean:
	rm -f -- $(OBJDIR)/*.o $(EXECDIR)/$(PROGRAM)
