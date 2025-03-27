#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

class PTree {
 public:
  PTree(double length, int depth);

  ~PTree() {}

 private:
  void pTree(sf::RectangleShape parentSquare, int depth);
  std::vector<sf::RectangleShape> shapes;
  double baseLength;
  int depth;
};
