// Copyright 2024 Chris Lambert

#include <iostream>

using std::ostream;
using std::string;

namespace PhotoMagic {
class FibLFSR {
 public:
  friend ostream &operator<<(ostream &out, const FibLFSR &lfsr);
  // constructor to create LFSR with the given initial seed and tap
  explicit FibLFSR(string seed);
  // simulate one step and return the new bit as 0 or 1
  int step();
  // simulate k steps and return k-bit integer
  int generate(int k);

 private:
  // helper functions
  int check(int index) const;
  string seed;
  int tap15, tap13, tap12, tap10;
  bool isValid;
};

ostream &operator<<(ostream &out, const FibLFSR &lfsr);

}  // namespace PhotoMagic
