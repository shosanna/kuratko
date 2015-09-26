INCLUDE=-Iinclude
CXXFLAGS=$(INCLUDE) -g -Wall -Wextra -std=c++14
LIB=-lstdc++ -lncurses

EXECDIR=./bin
OBJDIR=./obj
PROGRAM=map

SRC=$(wildcard src/*.cpp src/*.c)
TEMPOBJ=$(patsubst src/%.cpp, $(OBJDIR)/%.o, $(SRC))
OBJ=$(patsubst stc/%.c, $(OBJDIR)/%.o, $(TEMPOBJ))

.PHONY: $(PROGRAM)

all: $(PROGRAM)

$(OBJDIR)/%.o: src/%.c
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR)/%.o: src/%.cpp
	@$(CC) $(CXXFLAGS) -c $< -o $@

$(PROGRAM): $(OBJ)
	@$(CC) $(LIB) $(OBJ) -o $(EXECDIR)/$(PROGRAM)
	@$(EXECDIR)/$(PROGRAM)

clean:
	rm -f -- $(OBJDIR)/*.o $(EXECDIR)/$(PROGRAM)
