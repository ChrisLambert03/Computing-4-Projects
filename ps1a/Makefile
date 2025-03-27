# Compiler variables
CC = g++
CFLAGS = --std=c++17 -Wall -Werror -pedantic -g
LIB = -lsfml-graphics -lsfml-audio -lsfml-window -lsfml-system -lboost_unit_test_framework
# ar command variables
AR = ar
ARFLAGS = -rcs
# Your .hpp files
DEPS = FibLFSR.hpp
# Your compiled .o files
OBJECTS = FibLFSR.o
OBJECTS2 = main.o
# The name of your program
PROGRAM = test
PROGRAM2 = PhotoMagic
PHOTO_PROGRAM = static
# Static library name
STATIC_LIB = PhotoMagic.a

.PHONY: all clean lint

all: $(PROGRAM) $(PROGRAM2) $(PHOTO_PROGRAM)

# Wildcard recipe to make .o files from corresponding .cpp file
%.o: %.cpp $(DEPS)
	$(CC) $(CFLAGS) -c $<
# test:
$(PROGRAM): test.o $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^ $(LIB)
#Photomagic:
$(PROGRAM2): main.o $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^ $(LIB)
# PhotoMagic static library:
$(PHOTO_PROGRAM) : $(OBJECTS)
	$(AR) $(ARFLAGS) $(STATIC_LIB) $^
	
clean:
	rm *.o $(PROGRAM) $(PROGRAM2) $(STATIC_LIB)

lint:
	cpplint *.cpp *.hpp
