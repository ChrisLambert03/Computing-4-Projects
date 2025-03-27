// Copyright 2024 Chris Lambert
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <cmath>
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
  this->winScale = scale;
  this->winSize = windowSize;
  for (auto& body : bodies) {
    // load image/texture/sprite and set location
    body->loadImage();
    body->setLocation(scale, windowSize);
  }
}
void NB::Universe::step(double seconds) {
  const double g = 6.67e-11;

  CelestialBody* sun = nullptr;
  // look for the sun
  for (auto& body : bodies) {
    if (body->position() == sf::Vector2f(0.0, 0.0)) {
      sun = body.get();
    }
  }

  for (auto& body : bodies) {
    // ignore the sun
    if (body.get() == sun)
      continue;
    // get net force
    double netF, netX, netY, dX, dY, r;

    dX = sun->position().x - body->position().x;
    dY = sun->position().y - body->position().y;

    r = sqrt(pow(dX, 2) + pow(dY, 2));

    netF = g * body->getMass() * sun->getMass() / pow(r, 2);

    netX = netF * dX / r;
    netY = netF * dY / r;
    // get acceleration
    double aX, aY;

    aX = netX / body->getMass();
    aY = netY / body->getMass();

    double newVelx = body->velocity().x + seconds * aX;
    double newVely = body->velocity().y + seconds * aY;

    body->setVelocity(newVelx, newVely);

    double newPosx = body->position().x + seconds * newVelx;
    double newPosy = body->position().y + seconds * newVely;

    body->setPosition(newPosx, newPosy);
    body->setLocation(winScale, winSize);
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
    std::unique_ptr<CelestialBody> body = std::make_unique<CelestialBody>();
    input >> *body;
    body->loadImage();
    universe.bodies.push_back(std::move(body));
  }
  return input;
}
std::ostream& NB::operator<<(std::ostream& out, const Universe& universe) {
  out << universe.numBodies << endl;
  out << universe.rad << endl;
  for (const auto& body : universe.bodies) {
    out << *body << endl;
  }
  return out;
}
