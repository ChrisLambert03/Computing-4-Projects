// Copyright 2024 Chris Lambert
#pragma once
#include <string>
#include <vector>
#include <memory>
#include "CelestialBody.hpp"

namespace NB {
class Universe : public CelestialBody {
 public:
  friend std::istream& operator>>(std::istream& input, Universe& universe);
  friend std::ostream& operator<<(std::ostream& out, const Universe& universe);
  Universe() = default;
  explicit Universe(std::string);
  void load(float);
  int numPlanets() { return numBodies; }
  double radius() { return rad; }
  void step(double seconds);

  ~Universe() {}
  CelestialBody& operator[](size_t index) {
    if (index >= bodies.size()) {
      throw std::out_of_range("Index out of range");
    }
    return *bodies[index];
  }

 protected:
  void draw(sf::RenderTarget& target, sf::RenderStates states) const override {
    for (auto& body : bodies) {
      target.draw(*body, states);
    }
  }

 private:
  int numBodies;
  double rad;
  double winScale;
  double winSize;
  std::vector<std::unique_ptr<CelestialBody>> bodies;
};
std::istream& operator>>(std::istream& input, Universe& universe);
std::ostream& operator<<(std::ostream& os, const Universe& universe);
}  // namespace NB
