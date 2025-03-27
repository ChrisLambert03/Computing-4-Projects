#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <cmath>
#include <iostream>
#include <string>

#include "PTree.hpp"
using namespace std;

int main(int argc, char *argv[]) {
  double length;
  int depth;
  cin >> length >> depth;
  PTree test(length, depth);
}