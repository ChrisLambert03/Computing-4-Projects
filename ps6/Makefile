# Compiler variables
CC = g++
CFLAGS = --std=c++17 -Wall -Werror -pedantic -g
LIB = -lboost_unit_test_framework -O3
# ar command variables
AR = ar
ARFLAGS = -rcs
# Your .hpp files
DEPS = RandWriter.hpp
# Your compiled .o files
OBJECTS = RandWriter.o
# The name of your program
PROGRAM = TextWriter
TEST = test
# Static library name
STATIC_LIB = TextWriter.a

.PHONY: all clean lint

all: $(PROGRAM) $(STATIC_LIB) $(TEST)

# Wildcard recipe to make .o files from corresponding .cpp file
%.o: %.cpp $(DEPS)
	$(CC) $(CFLAGS) -c $<
# TextWriter:
$(PROGRAM): main.o $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^ $(LIB)

# TextWriter.a static library:
$(STATIC_LIB) : $(OBJECTS)
	$(AR) $(ARFLAGS) $@ $^

#boost test:
 $(TEST): test.o $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^ $(LIB)
	
clean:
	rm *.o $(PROGRAM) $(STATIC_LIB) $(TEST)

lint:
	cpplint *.cpp *.hpp
