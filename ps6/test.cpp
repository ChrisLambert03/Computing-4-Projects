// Copyright 2024 Chris Lambert
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE Main
#include <fstream>
#include <sstream>
#include <boost/test/unit_test.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include "RandWriter.hpp"

BOOST_AUTO_TEST_CASE(testOrder) {
  RandWriter rw("hello world", 2);
  BOOST_CHECK_EQUAL(rw.orderK(), 2);
}
BOOST_AUTO_TEST_CASE(testOrderZero) {
  RandWriter rw("hello world hello world", 0);
  BOOST_CHECK_EQUAL(rw.orderK(), 0);
}

BOOST_AUTO_TEST_CASE(testFreq) {
  RandWriter rw("hello world", 1);
  BOOST_CHECK_EQUAL(rw.freq("h"), 1);
  BOOST_CHECK_EQUAL(rw.freq("l"), 3);
  BOOST_CHECK_EQUAL(rw.freq("u"), 0);

  BOOST_REQUIRE_THROW(rw.freq("fdgf"), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(testFreqChar) {
  RandWriter rw("hello world", 2);
  BOOST_CHECK_EQUAL(rw.freq("he", 'l'), 1);
  BOOST_CHECK_EQUAL(rw.freq("wo", 'l'), 0);

  BOOST_REQUIRE_THROW(rw.freq("hel", 'a'), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(testKRand) {
  RandWriter rw("hello world", 2);
  BOOST_CHECK(rw.kRand("he") == 'l');
  BOOST_REQUIRE_THROW(rw.kRand("xyz"), std::invalid_argument);
}
BOOST_AUTO_TEST_CASE(testKRandZero) {
  RandWriter rw("hello world", 0);
  BOOST_REQUIRE_THROW(rw.kRand("he"), std::invalid_argument);
  BOOST_REQUIRE_THROW(rw.kRand("xyz"), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(testGenerate) {
  RandWriter rw("hello world", 2);
  BOOST_CHECK_EQUAL(rw.generate("he", 16).length(), 16);
  BOOST_CHECK_EQUAL(rw.generate("he", 16).substr(0, 2), "he");

  BOOST_REQUIRE_THROW(rw.generate("xyz", 5), std::invalid_argument);
}
