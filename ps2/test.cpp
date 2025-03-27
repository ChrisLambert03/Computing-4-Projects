#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>

using namespace std;

void drawTree(sf::RenderWindow &window, sf::RectangleShape rect, float angle, int depth) {
  if (depth == 0) {
    return;
  }

  // Draw the current rectangle
  window.draw(rect);

  // Calculate the next rectangle's position and size
  sf::Vector2f size = rect.getSize();
  sf::Vector2f position = rect.getPosition();
  float newWidth = size.x * cos(angle);
  float newHeight = size.y * sin(angle);

  // Create the next rectangle
  sf::RectangleShape nextRect(sf::Vector2f(newWidth, newHeight));
  nextRect.setFillColor(sf::Color::White);
  nextRect.setOutlineColor(sf::Color::Black);
  nextRect.setOutlineThickness(1);
  nextRect.setPosition(position.x + size.x - newWidth, position.y - newHeight);
  nextRect.setRotation(-45);

  // Recursively draw the next branches
  drawTree(window, nextRect, angle, depth - 1);
  nextRect.setRotation(45);
  drawTree(window, nextRect, angle, depth - 1);
}

int main() {
  int depth = 5;                     // Depth of the tree
  float angle = 45 * M_PI / 180.0f;  // 45 degrees in radians

  sf::RenderWindow window(sf::VideoMode(800, 600), "Pythagorean Tree");
  window.clear(sf::Color::Black);

  // Create the trunk of the tree
  sf::RectangleShape trunk(sf::Vector2f(20, 100));
  trunk.setFillColor(sf::Color::White);
  trunk.setPosition(390, 500);
  trunk.setRotation(-90);

  drawTree(window, trunk, angle, depth);

  window.display();

  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        window.close();
      }
    }
  }

  return 0;
}
