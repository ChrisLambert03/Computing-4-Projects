# PS5: DNA Alignment

## Contact

Name: Chris Lambert
Section: 203
Time to Complete: ~8 hours

Partner: I have no partner

## Description

This program will accept 2 string arguments passed in from stdin. After reading in the strings the program will setup a 2d matrix with the w string going along the top row and leftmost column. The progam will then determine the edit distance among the 2 strings and print out the sequence with appropriate gaps and cost per each index.

### Features

The Levenshtein algorithm is implemented and employed recursively onto the matrix to compute the edit distance. The data structures associated with this program was a vector of vectors containing strings to mimick matrix operations.

### Testing

- The testConstructor case ensures that the class initializes correctly with the provided strings.
- testOptDistance checks if the optimal edit distance calculation is correct
- testStreamOperator verifies that the class can be properly initialized from a stream
- testIndex checks if the class throws an exception when accessing out-of-range indices.

### Issues

- N/A

### Example

Do one additional test case by hand. It should be constructed in such a way that you know the correct output before running your program on it, and it should be a "corner case" that helps check if your program handles all special situations correctly.

Please list:

- a copy of the test case input : a = "hello", b = "world"
- the expected test case output:
  Edit Distance = 4
  h w 1
  e o 1
  l r 1
  l l 0
  o d 1
- whether your program ran correctly on it or not:
  - it did run correctly

### Specs

My Computer:
Memory: 16gb DDR4
Processors: i7-1165G7 @ 2.80 Ghz x4

### Runs

(See issue)
Fill in the table with the results of running your code on both your and your partner's computers.

| data file       | distance | memory (mb) | time (seconds) | partner time |
| --------------- | -------- | ----------- | -------------- | ------------ |
| ecoli2500.txt   | 120      | 191.4       | 0.185          |              |
| ecoli5000.txt   | 162      | 764.1       | 0.870          |              |
| ecoli10000.txt  | 225      | 2982        | 2.64           |              |
| ecoli20000.txt  |          |             |                |              |
| ecoli50000.txt  |          |             |                |              |
| ecoli100000.txt |          |             |                |              |

### Time

Assume the two strings are the same length (M = N). By applying the doubling method to the data points that you obtained, estimate the running time of youu program in seconds as a polynomial function of N, in the form a \* N^b for some constants a and b. Determine the largest input your program can handle if it is limited to one day of computation.

Provide a brief justification/explanation of how you applied the doubling method, and if you data seems not to work, describe what went wrong and use the sample data instead.

- a = 100
- b = 2
- largest N = 10

### Memory

Assume the two strings are the same length (M = N). Look at your code and determine how much memory it requires as a polynomial function of N, in the form a \* N^b for some constants a and b. Determine the largest input size your computer can handle if limited to 8GiB of RAM.

- a = 20
- b = 2
- largest N = 16384

### Valgrind

Run valgrind and list any errors you see. Identify whether the memory usage reported by valgrind almost matches the calculations in the previous section.

## Pair Programming

N/A

## Extra Credit

- For my implememted min3 function I actually used std::min and just nested the parameters because it will output th same value regardless of order
- for the different optimization levels:
- O0 - does no optimization at all even the most basic ones that the compiler will do by default if no flag is present
- O1 - does a little optimazation such as inline functions
- O2 - optimizes more aggressively such unrolling for loops to lessen iteration
- O3 - will optimize the program to its fullest extent that may result in larger binary files and compile time

## Acknowledgements

N/A
