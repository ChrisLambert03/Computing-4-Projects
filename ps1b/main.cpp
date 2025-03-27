// Copyright 2024 Chris Lambert
//  using SFML to load a file, manipulate its pixels, write it to disk

// g++ -o Photomagic main.cpp PhotoMagic.cpp FibLFSR.cpp -lsfml-graphics -lsfml-window -lsfml-system
#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

#include "FibLFSR.hpp"
#include "PhotoMagic.hpp"

using PhotoMagic::FibLFSR;
using PhotoMagic::transform;

int main(int argc, char* argv[]) {
  // read in command line arguments and construct the seed
  string input = argv[1];
  string output = argv[2];
  string seed = argv[3];

  FibLFSR algorithm(seed);

  sf::Image image;
  if (!image.loadFromFile(input))
    return -1;
  // encrypt the first image
  transform(image, &algorithm);
  // save the encrypted image

  sf::Vector2u size = image.getSize();
  sf::RenderWindow window1(sf::VideoMode(size.x, size.y), "Encrypted Image");

  // Encrytped image sprite
  sf::Texture texture;
  texture.loadFromImage(image);

  sf::Sprite sprite;
  sprite.setTexture(texture);

  while (window1.isOpen()) {
    sf::Event event;
    while (window1.pollEvent(event)) {
      if (event.type == sf::Event::Closed)
        window1.close();
    }
    window1.clear();
    window1.draw(sprite);
    window1.display();
  }

  //   write the file
  if (!image.saveToFile(output))
    return -1;

  return 0;
}
