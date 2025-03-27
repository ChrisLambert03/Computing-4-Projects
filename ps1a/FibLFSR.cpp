// Copyright 2024 Chris Lambert

#include "FibLFSR.hpp"

#include <cmath>
#include <exception>
#include <iostream>
#include <string>

using PhotoMagic::FibLFSR;

// defines your seed
FibLFSR::FibLFSR(string seed) : seed(seed), isValid(true) {
  // checking for a valid seed
  if (seed.length() != 16) {
    isValid = false;
  }
  for (auto i : seed) {
    if (i != '0' && i != '1') {
      isValid = false;
      break;
    }
  }
}
// helper function for char to int conversion
int FibLFSR::check(int index) const { return seed[index] == '0' ? 0 : 1; }

int FibLFSR::step() {
  // all invalid seeds get stored but not manipulated
  if (!this->isValid)
    return 0;

  tap15 = check(0);
  tap13 = check(2);
  tap12 = check(3);
  tap10 = check(5);
  // automatic type conversion with 1 and 0
  bool step = tap15;
  step = (step != tap13);
  step = (step != tap12);
  step = (step != tap10);

  string newSeed = this->seed.substr(1, this->seed.length() - 1);
  newSeed += (step) ? '1' : '0';
  this->seed = newSeed;

  return step;
}

int FibLFSR::generate(int k) {
  // invalid parameters wont be manipulated and return 0
  if (k > 16 || k < 0) {
    return 0;
  }
  if (!this->isValid) {
    return 0;
  }
  // perform the step k times
  for (int i = 0; i < k; i++) {
    step();
  }
  // splices the string to the k bit sequence and converts it using a reverse iterator/counter
  string binary = seed.substr(seed.length() - k, k);
  int count = 0;
  int finalValue = 0;

  for (auto i = binary.rbegin(); i != binary.rend(); ++i) {
    if (*i == '1')
      finalValue += pow(2, count);
    count++;
  }
  return finalValue;
}
// ostream operator overload
ostream &PhotoMagic::operator<<(ostream &out, const FibLFSR &lfsr) {
  out << lfsr.seed;
  return out;
}
