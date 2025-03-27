// Copyright 2024 Chris Lambert
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include "Universe.hpp"
#include "CelestialBody.hpp"

using std::cin;
using std::string;

int main(int argc, char* argv[]) {
  double elapsedTime = 0.0;
  double T = std::stod(argv[1]);
  double deltaT = std::stod(argv[2]);

  NB::Universe universe;
  cin >> universe;

  sf::RenderWindow window(sf::VideoMode(500, 500), "The Solar System!");
  // Extra credit background image
  sf::Texture backgroundTexture;
  if (!backgroundTexture.loadFromFile("background.jpg")) {
    std::cerr << "Error loading background image" << std::endl;
  }
  // scale the background up to fill the screen
  sf::Vector2u windowSize = window.getSize();
  sf::Vector2u textureSize = backgroundTexture.getSize();
  float scaleX = static_cast<float>(windowSize.x) / textureSize.x;
  float scaleY = static_cast<float>(windowSize.y) / textureSize.y;
  sf::Sprite backgroundSprite(backgroundTexture);
  backgroundSprite.setScale(scaleX, scaleY);

  // loads the universe with respect to the window size.
  universe.load(window.getSize().x);
  sf::Clock clock;
  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed)
        window.close();
    }

    if (elapsedTime < T) {
      universe.step(deltaT);
      elapsedTime += deltaT;
    } else {
      window.close();
    }
    window.setTitle(" The Solar System! - Elapsed Time: " +
                    std::to_string(clock.getElapsedTime().asSeconds()) + " seconds");

    window.clear(sf::Color::Black);
    window.draw(backgroundSprite);
    window.draw(universe);
    window.display();
  }
  std::cout << universe << std::endl;
}
