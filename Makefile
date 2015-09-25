CXXFLAGS=-g -Wall -Wextra -std=c++14
LIB=-lstdc++

SRC=$(wildcard *.cpp)

OBJDIR=obj
OBJ = $(patsubst %.cpp, $(OBJDIR)/%.o, $(SRC))

PROGRAM=boo
.PHONY: $(PROGRAM)

all: $(PROGRAM)

$(OBJDIR)/%.o: %.cpp
	$(CC) $(CXXFLAGS) -c $< -o $@

$(PROGRAM): $(OBJ)
	$(CC) $(LIB) $(OBJ) -o $(PROGRAM)
	perf stat ./$(PROGRAM)

clean:
	rm -f -- $(OBJDIR)/*.o
