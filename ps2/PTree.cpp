#include "PTree.hpp"

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <cmath>
#include <iostream>
#include <string>

using namespace std;
using sf::Vector2f;

Vector2f CalcOffset(sf::RectangleShape square, Vector2f offset);
Vector2f CalcOffset2(sf::RectangleShape square, Vector2f offset);

PTree::PTree(double length, int depth) : baseLength(length), depth(depth) {
  sf::RectangleShape square;
  square.setSize(Vector2f(baseLength, baseLength));
  square.setOrigin(square.getSize().x / 2, square.getSize().y / 2);
  square.setFillColor(sf::Color::Black);
  square.setPosition(6 * length / 2, 4 * length - (baseLength / 2));

  cout << square.getRotation() << endl;

  pTree(square, depth);

  sf::RenderWindow window1(sf::VideoMode(6 * length, 4 * length), "Pythagorean Tree");
  while (window1.isOpen()) {
    sf::Event event;
    while (window1.pollEvent(event)) {
      if (event.type == sf::Event::Closed)
        window1.close();
    }
    window1.clear(sf::Color::White);
    window1.draw(square);
    for (auto i = shapes.begin(); i != shapes.end(); ++i) {
      window1.draw(*i);
    }
    window1.display();
  }
}

void PTree::pTree(sf::RectangleShape parent, int depth) {
  if (depth == 0)
    return;

  auto newSize = [](Vector2f vector) { return Vector2f(vector.x * sin(45 * M_PI / 180.0f), vector.y * sin(45 * M_PI / 180.0f)); };
  auto getCorner = [](sf::RectangleShape x) { return x.getTransform().transformPoint(x.getPoint(1)); };
  auto newOffset = [](sf::RectangleShape x) { return Vector2f(x.getSize().x / 2.0, x.getSize().y / 2.0); };
  auto getCorner1 = [](sf::RectangleShape x) { return x.getTransform().transformPoint(x.getPoint(0)); };
  auto offset = newOffset(parent);

  sf::RectangleShape childShape1;
  childShape1.setSize(newSize(parent.getSize()));
  childShape1.setOrigin(childShape1.getSize().x / 2.0, childShape1.getSize().y / 2.0);
  childShape1.setFillColor(sf::Color::Blue);
  childShape1.rotate(parent.getRotation() + 45);
  childShape1.setPosition(getCorner(parent) + CalcOffset(childShape1, offset));
  // cout << childShape1.getRotation() << endl;

  sf::RectangleShape childShape2;
  childShape2.setSize(newSize(parent.getSize()));
  childShape2.setOrigin(childShape2.getSize().x / 2.0, childShape2.getSize().y / 2.0);
  childShape2.setFillColor(sf::Color::Red);
  childShape2.rotate(parent.getRotation() - 45);
  childShape2.setPosition(getCorner1(parent) + CalcOffset2(childShape2, offset));
  cout << "child shape 2 roto: " << childShape2.getRotation() << endl;

  this->shapes.push_back(childShape1);
  this->shapes.push_back(childShape2);

  // Recursively call pTree for each child shape
  pTree(childShape1, depth - 1);
  pTree(childShape2, depth - 1);
}

Vector2f CalcOffset(sf::RectangleShape square, Vector2f offset) {
  auto rotation = square.getRotation();

  if (rotation == 0) {
    return Vector2f(-offset.x / sqrt(2), -offset.y / sqrt(2));
  } else if (rotation == 45) {
    return Vector2f(0, -offset.y);
  } else if (rotation == 90) {
    return Vector2f(offset.x / sqrt(2), -offset.y / sqrt(2));
  } else if (rotation == 135) {
    return Vector2f(offset.x, 0);
  } else if (rotation == 180) {
    return Vector2f(offset.x / sqrt(2), offset.y / sqrt(2));
  } else if (rotation == 225) {
    return Vector2f(0, offset.y);
  } else if (rotation == 270) {
    return Vector2f(-offset.x / sqrt(2), offset.y / sqrt(2));
  } else if (rotation == 315) {
    return Vector2f(-offset.x, 0);
  }
}

Vector2f CalcOffset2(sf::RectangleShape square, Vector2f offset) {
  auto rotation = square.getRotation();

  if (rotation == 0) {
    return Vector2f(offset.x / sqrt(2), -offset.y / sqrt(2));
  } else if (rotation == 45) {
    return Vector2f(offset.x, 0);
  } else if (rotation == 90) {
    return Vector2f(offset.x / sqrt(2), offset.y / sqrt(2));
  } else if (rotation == 135) {
    return Vector2f(0, offset.y);
  } else if (rotation == 180) {
    return Vector2f(-offset.x / sqrt(2), offset.y / sqrt(2));
  } else if (rotation == 225) {
    return Vector2f(-offset.x, 0);
  } else if (rotation == 270) {
    return Vector2f(-offset.x / sqrt(2), -offset.y / sqrt(2));
  } else if (rotation == 315) {
    return Vector2f(0, -offset.y);
  }
}