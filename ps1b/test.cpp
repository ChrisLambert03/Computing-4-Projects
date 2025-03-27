// Copyright 2022
// By Dr. Rykalova
// Editted by Dr. Daly
// test.cpp for PS1a
// updated 1/8/2024

#include <iostream>
#include <sstream>
#include <string>

#include "FibLFSR.hpp"

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE Main
#include <boost/test/unit_test.hpp>

using PhotoMagic::FibLFSR;

BOOST_AUTO_TEST_CASE(testStepInstr) {
  FibLFSR l("1011011000110110");
  BOOST_REQUIRE_EQUAL(l.step(), 0);
  BOOST_REQUIRE_EQUAL(l.step(), 0);
  BOOST_REQUIRE_EQUAL(l.step(), 0);
  BOOST_REQUIRE_EQUAL(l.step(), 1);
  BOOST_REQUIRE_EQUAL(l.step(), 1);
  BOOST_REQUIRE_EQUAL(l.step(), 0);
  BOOST_REQUIRE_EQUAL(l.step(), 0);
  BOOST_REQUIRE_EQUAL(l.step(), 1);
}

BOOST_AUTO_TEST_CASE(testGenerateInstr) {
  FibLFSR l("1011011000110110");
  BOOST_REQUIRE_EQUAL(l.generate(9), 51);
}
BOOST_AUTO_TEST_CASE(testGenerateAfterStep) {
  FibLFSR l("1011011000000111");
  l.step();
  l.step();
  BOOST_REQUIRE_EQUAL(l.generate(8), 123);
}
BOOST_AUTO_TEST_CASE(testGenerateMaxBits) {
  FibLFSR l("1011011000000111");
  BOOST_REQUIRE_EQUAL(l.generate(16), 7872);
}
BOOST_AUTO_TEST_CASE(testOutputStream) {
  FibLFSR l("1011011000000111");
  std::stringstream output;
  std::streambuf* buffer = std::cout.rdbuf();  // Save cout buffer
  std::cout.rdbuf(output.rdbuf());             // redirect cout to output object
  std::cout << l;
  std::cout.rdbuf(buffer);  // restore cout
  BOOST_CHECK_EQUAL(output.str(), "1011011000000111");
}
BOOST_AUTO_TEST_CASE(testOutputAfterInstr) {
  FibLFSR l("1011011000000111");
  l.step();
  l.step();
  l.generate(13);
  std::stringstream output;
  std::streambuf* buffer = std::cout.rdbuf();
  std::cout.rdbuf(output.rdbuf());
  std::cout << l;
  std::cout.rdbuf(buffer);
  BOOST_CHECK_EQUAL(output.str(), "1000111101100000");
}
