// Copyright 2024 Chris Lambert
#pragma once
#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>

namespace NB {

class CelestialBody : public sf::Drawable {
 public:
  friend std::istream& operator>>(std::istream& input, CelestialBody& body);
  friend std::ostream& operator<<(std::ostream& out, const CelestialBody& body);

  CelestialBody();
  ~CelestialBody() {}

  void setLocation(double scale, float windowSize) {
    this->sprite.setPosition(xpos * scale + (windowSize / 2), ypos * scale + (windowSize / 2));
  }
  sf::Vector2f position() { return sf::Vector2f(xpos, ypos); }
  sf::Vector2f velocity() { return sf::Vector2f(xvel, yvel); }
  double getMass() { return mass; }
  void loadImage();

 protected:
  void draw(sf::RenderTarget& target, sf::RenderStates states) const override {
    target.draw(sprite, states);
  }

 private:
  double xpos;
  double ypos;
  double xvel;
  double yvel;
  double mass;
  std::string planet;
  sf::Texture texture;
  sf::Sprite sprite;
  sf::Image image;
};
std::istream& operator>>(std::istream& input, CelestialBody& body);
std::ostream& operator<<(std::ostream& os, const CelestialBody& body);
}  // namespace NB
