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
#include "EDistance.hpp"

BOOST_AUTO_TEST_CASE(testConstructor) {
  string a = "peter";
  string b = "pan";

  EDistance ed(a, b);
  BOOST_CHECK_EQUAL(ed[0].size(), 5);
  BOOST_CHECK_EQUAL(ed[1][0], "p");
  BOOST_CHECK_EQUAL(ed[0][1], "p");
}

BOOST_AUTO_TEST_CASE(testOptDistance) {
  EDistance ed("peterpan", "neverland");
  BOOST_CHECK_EQUAL(ed.optDistance(), 5);
}

BOOST_AUTO_TEST_CASE(testStreamOperator) {
  std::stringstream ss("AGGTAGCAGAAC\nCGGTCAGTCA\n");
  EDistance ed;
  ss >> ed;
  BOOST_CHECK_EQUAL(ed[1][0], "A");
  BOOST_CHECK_EQUAL(ed[0][1], "C");
}
BOOST_AUTO_TEST_CASE(testIndex) {
  std::stringstream ss("AGGTAGCAGAAC\nCGGTCAGTCA\n");
  EDistance ed;
  ss >> ed;
  BOOST_REQUIRE_THROW(ed[15], std::out_of_range);
}