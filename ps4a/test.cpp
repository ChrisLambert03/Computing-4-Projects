// Copyright 2024 Chris Lambert
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE Main
#include <fstream>
#include <sstream>
#include <boost/test/unit_test.hpp>
#include "CelestialBody.hpp"
#include "Universe.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>

BOOST_AUTO_TEST_CASE(celestial_body_IO_test) {
  std::string line("1.4960e+11  0.0000e+00  0.0000e+00  2.9800e+04  5.9740e+24    earth.gif");
  NB::CelestialBody body;
  std::istringstream(line) >> body;

  std::ostringstream oss;
  oss << body;

  BOOST_CHECK_EQUAL(oss.str(),
                    "1.496000e+11 0.000000e+00 0.000000e+00 2.980000e+04 5.974000e+24 earth.gif");
}

BOOST_AUTO_TEST_CASE(universe_IO_test) {
  NB::Universe universe("planets.txt");
  std::ostringstream oss;
  oss << universe;
  BOOST_CHECK(oss);
}

BOOST_AUTO_TEST_CASE(universe_getter_test) {
  NB::Universe universe("planets.txt");

  // Check if the universe is loaded with the correct number of bodies and radius
  BOOST_CHECK_EQUAL(universe.numPlanets(), 5);
  BOOST_CHECK_EQUAL(universe.radius(), 2.50e+11);
}
BOOST_AUTO_TEST_CASE(celestial_body_getter_test) {
  std::string line("1.4960e+11  0.0000e+00  0.0000e+00  2.9800e+04  5.9740e+24    earth.gif");
  NB::CelestialBody body;
  std::istringstream(line) >> body;

  // Check if the universe is loaded with the correct number of bodies and radius
  BOOST_CHECK_EQUAL(body.velocity().x, 0);
  double a = 1.49599994e+11;
  BOOST_CHECK_CLOSE(body.position().x, a, 0.0001);
}
