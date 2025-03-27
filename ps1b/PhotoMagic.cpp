// Copyright 2023 Chris Lambert
#include "PhotoMagic.hpp"

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

#include "FibLFSR.hpp"

void PhotoMagic::transform(sf::Image& image, FibLFSR* seed) {
  auto size = image.getSize();

  for (unsigned int i = 0; i < size.x; ++i) {
    for (unsigned int j = 0; j < size.y; ++j) {
      sf::Color p = image.getPixel(i, j);

      auto p_red = p.r;
      auto p_green = p.g;
      auto p_blue = p.b;

      int r_seed = seed->generate(15);
      auto new_red = p_red ^ r_seed;

      int g_seed = seed->generate(15);
      auto new_green = p_green ^ g_seed;

      int b_seed = seed->generate(15);
      auto new_blue = p_blue ^ b_seed;

      sf::Color color(new_red, new_green, new_blue);

      image.setPixel(i, j, color);
    }
  }
}
