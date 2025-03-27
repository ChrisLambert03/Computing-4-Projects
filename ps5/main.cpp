// Copyright 2024 Chris Lambert
#include <iostream>
#include <string>
#include "EDistance.hpp"
#include <SFML/System.hpp>

using std::cin;
using std::cout;
using std::endl;

int main() {
  sf::Clock clock;
  EDistance test;
  cin >> test;

  sf::Time t = clock.getElapsedTime();

  cout << test.alignment() << endl;

  cout << "Elapsed time: " << t.asSeconds() << endl;

  return 0;
}
