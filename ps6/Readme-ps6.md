# PS6: RandWriter

## Contact

Name: Chris Lambert
Section: 203
Time to Complete: 6 hours

## Description

- This program fully works

This project implements a simplified text generator using Markov chains, inspired by Claude Shannon's work in information theory. The program creates a model of text based on the frequency of character sequences (k-grams) and uses this model to generate new text. This algorithm demonstrates how Markov chains can be used to simulate the structure of natural language, with applications in various fields such as speech recognition and data compression. When the progr iams executed it is given 2 command line arguments for the order k and the sentence generated of length L. The input data is read from stdin.

### Features

- There are 2 map data structures to store the kgram data, one maps the frequency of the kgram and the other the frequency of the k+1 gram.
- The alphabet, input text, and order are stored as private variables
- If a function were to throw an exception it will be handled by calling the same functions with its curcular substring as the parameter

### Testing

- Helper functions throw invalid argument exceptions when the kgram is not the right length so I tested the helper functions individually

### Lambda

- There is a lambda expression that is utilized to return the circular substring of the generated text

### Issues

- N/A

### Extra Credit

- N/A

## Acknowledgements

- N/A
