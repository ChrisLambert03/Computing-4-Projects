// Copyright 2024 Chris Lambert
#include <iostream>
#include <sstream>
#include <string>

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE Main
#include <boost/test/unit_test.hpp>

#include "Sokoban.hpp"

BOOST_AUTO_TEST_CASE(sokoban_initialization_test) {
  SB::Sokoban sokoban("level1.lvl");

  // Check if width and height are initialized correctly
  BOOST_CHECK_EQUAL(sokoban.getWidth(), 10);
  BOOST_CHECK_EQUAL(sokoban.getHeight(), 10);
  // Add more checks for other initial conditions
}

BOOST_AUTO_TEST_CASE(sokoban_move_test) {
  SB::Sokoban sokoban("level1.lvl");

  // Move player up
  sokoban.movePlayer(SB::Direction::Up);
  BOOST_CHECK_EQUAL(sokoban.playerLoc().first, 5);
  BOOST_CHECK_EQUAL(sokoban.playerLoc().second, 3);

  // Move player left
  sokoban.movePlayer(SB::Direction::Left);
  BOOST_CHECK_EQUAL(sokoban.playerLoc().first, 5);
  BOOST_CHECK_EQUAL(sokoban.playerLoc().second, 2);

  // Move player down
  sokoban.movePlayer(SB::Direction::Down);
  BOOST_CHECK_EQUAL(sokoban.playerLoc().first, 6);
  BOOST_CHECK_EQUAL(sokoban.playerLoc().second, 2);

  // Move player right
  sokoban.movePlayer(SB::Direction::Right);
  BOOST_CHECK_EQUAL(sokoban.playerLoc().first, 6);
  BOOST_CHECK_EQUAL(sokoban.playerLoc().second, 3);
}

BOOST_AUTO_TEST_CASE(sokoban_win_test) {
  SB::Sokoban sokoban("level1.lvl");

  // Check if the game is won
  BOOST_CHECK_EQUAL(sokoban.isWon(), false);
}
