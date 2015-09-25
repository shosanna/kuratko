CXXFLAGS=-g -Wall -Wextra -std=c++14
LIB=-lstdc++

EXECDIR=./bin
OBJDIR=./obj
PROGRAM=map

SRC=$(wildcard *.cpp *c)
TEMPOBJ=$(patsubst %.cpp, $(OBJDIR)/%.o, $(SRC))
OBJ=$(patsubst %.c, $(OBJDIR)/%.o, $(TEMPOBJ))

.PHONY: $(PROGRAM)

all: $(PROGRAM)

$(OBJDIR)/%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR)/%.o: %.cpp
	@$(CC) $(CXXFLAGS) -c $< -o $@

$(PROGRAM): $(OBJ)
	@$(CC) $(LIB) $(OBJ) -o $(EXECDIR)/$(PROGRAM)
	@$(EXECDIR)/$(PROGRAM)

clean:
	rm -f -- $(OBJDIR)/*.o $(EXECDIR)/$(PROGRAM)
