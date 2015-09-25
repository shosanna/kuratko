CXXFLAGS=-g -Wall -Wextra -std=c++14
LIB=-lstdc++

EXECDIR=./bin
OBJDIR=./obj
PROGRAM=btree

SRC=$(wildcard *.cpp)
OBJ=$(patsubst %.cpp, $(OBJDIR)/%.o, $(SRC))

.PHONY: $(PROGRAM)

all: $(PROGRAM)

$(OBJDIR)/%.o: %.cpp
	$(CC) $(CXXFLAGS) -c $< -o $@

$(PROGRAM): $(OBJ)
	$(CC) $(LIB) $(OBJ) -o $(EXECDIR)/$(PROGRAM)
	perf stat $(EXECDIR)/$(PROGRAM)

clean:
	rm -f -- $(OBJDIR)/*.o $(EXECDIR)/$(PROGRAM)
