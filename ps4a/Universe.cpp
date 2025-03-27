// Copyright 2024 Chris Lambert
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include "Universe.hpp"
#include "CelestialBody.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>

using std::cout;
using std::endl;
using std::string;
NB::Universe::Universe(string filename) {
  std::ifstream file(filename);
  if (!file.is_open()) {
    std::cerr << "Error opening file." << std::endl;
  }

  file >> *this;

  file.close();
}
void NB::Universe::load(float windowSize) {
  double scale = (windowSize / 2) / this->rad;
  for (auto i = bodies.begin(); i != bodies.end(); i++) {
    // load image/texture/sprite and set location
    i->loadImage();
    i->setLocation(scale, windowSize);
  }
}
// iostream overloads
std::istream& NB::operator>>(std::istream& input, Universe& universe) {
  int newNumBodies;
  double newRadius;

  input >> newNumBodies >> newRadius;

  universe.numBodies = newNumBodies;
  universe.rad = newRadius;
  universe.bodies.clear();

  for (int i = 0; i < universe.numBodies; ++i) {
    CelestialBody body;
    input >> body;
    body.loadImage();
    universe.bodies.push_back(body);
  }
  return input;
}
std::ostream& NB::operator<<(std::ostream& out, const Universe& universe) {
  out << universe.numBodies << endl;
  out << universe.rad << endl;
  for (const CelestialBody& body : universe.bodies) {
    out << body << endl;
  }
  return out;
}
