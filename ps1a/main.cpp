// Copyright 2024 Chris Lambert
#include <iostream>

#include "FibLFSR.hpp"

using PhotoMagic::FibLFSR;

int main(void) {
  FibLFSR l("1011011000110110");

  l.step();
  l.step();

  std::cout << l << " Generated with 5 : " << l.generate(5) << std::endl;

  return 0;
}
