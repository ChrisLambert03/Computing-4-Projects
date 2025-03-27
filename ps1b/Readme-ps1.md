# PS1: LFSR / PhotoMagic

## Contact

Name:Chris Lambert

Section: 203

Time to Complete: ~3 hours

## Description

This projects implements a Fibonnaci Linear Feedback Shift Register into a class. Once create an object with a 16 bit binary seed you have access to 3 member functions.
step() - allows you to shift the sequence of bit one step by using predetermined taps and XOR them together
generate(n) - will perform step() n times then return the nth integer bit
getSeed() - returns the seed in string form

Part B: the program uses the LFSR algorithm to encrypt and image definied as an argument by the user and the outputs the encrypted image in a window as well as save it to the current directory

### Features

For the step and generate methods above I included a way to determine if the seed was valid or not. I did that by making sure to check if the seed had the right amount of characters and is a binary sequence.

### Issues

I do not have any issues.

### Tests

Boost Test cases were made to test the member functions and constructor with valid and invalid paratemers, as well as testing the functions after a few member function have been called. Depending on the arguments given the program may or may not manipulate the data within the object via its member functions and jsut return 0.

### Extra Credit

N/A

## Acknowledgements

I used cplusplus.com as a reference for the libraries in the include directives.
Also I googled how to redirect the standard output into an object rather than the console because it did not pass the Boost Test due to it printing to the console. Here is the link: https://stackoverflow.com/questions/10150468/how-to-redirect-cin-and-cout-to-files
