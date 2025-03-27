// Copyright 2024 Chris Lambert
#include "CelestialBody.hpp"
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>

NB::CelestialBody::CelestialBody() = default;

void NB::CelestialBody::loadImage() {
  if (!this->image.loadFromFile(this->planet)) {
    std::cerr << " Error loading an image " << std::endl;
  }
  if (!this->texture.loadFromImage(image)) {
    std::cerr << " Error loading a texture " << std::endl;
  }
  this->sprite.setTexture(texture);

  sf::FloatRect rect = sprite.getLocalBounds();
  sprite.setOrigin(rect.left + rect.width / 2.0f, rect.top + rect.height / 2.0f);
}

// iostream overloads
std::istream& NB::operator>>(std::istream& input, CelestialBody& body) {
  input >> body.xpos >> body.ypos >> body.xvel >> body.yvel >> body.mass >> body.planet;
  return input;
}
std::ostream& NB::operator<<(std::ostream& out, const CelestialBody& body) {
  out << std::scientific << body.xpos << " " << body.ypos << " "
      << body.xvel << " " << body.yvel << " " << body.mass << " " << body.planet;
  return out;
}
