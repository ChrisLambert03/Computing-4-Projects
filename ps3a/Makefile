# Compiler variables
CC = g++
CFLAGS = --std=c++17 -Wall -Werror -pedantic -g
LIB = -lsfml-graphics -lsfml-audio -lsfml-window -lsfml-system -lboost_unit_test_framework
# ar command variables
AR = ar
ARFLAGS = -rcs
# Your .hpp files
DEPS = Sokoban.hpp
# Your compiled .o files
OBJECTS = Sokoban.o
# The name of your program
PROGRAM = Sokoban
TEST = test
# Static library name
STATIC_LIB = Sokoban.a

.PHONY: all clean lint

all: $(PROGRAM) $(STATIC_LIB) $(TEST)

# Wildcard recipe to make .o files from corresponding .cpp file
%.o: %.cpp $(DEPS)
	$(CC) $(CFLAGS) -c $<
# Sokoban:
$(PROGRAM): main.o $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^ $(LIB)

# static library:
$(STATIC_LIB) : $(OBJECTS)
	$(AR) $(ARFLAGS) $@ $^

#boost test:
$(TEST): test.o $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^ $(LIB)
	
clean:
	rm *.o $(PROGRAM) $(STATIC_LIB)

lint:
	cpplint *.cpp *.hpp
