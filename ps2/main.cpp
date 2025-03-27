// Copyright 2024 Chris Lambert
//  using SFML to load a file, manipulate its pixels, write it to disk

// g++ -o ps2 main.cpp -lsfml-graphics -lsfml-window -lsfml-system
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <cmath>
#include <iostream>
#include <string>

using namespace std;
using sf::Vector2f;

Vector2f CalcOffset(sf::RectangleShape square, Vector2f offset);

int main(int argc, char* argv[]) {
  // read in command line arguments and construct the seed (start with #1)

  // Initial square
  sf::RectangleShape square;
  square.setOrigin(square.getSize().x / 2, square.getSize().y / 2);
  square.setSize(Vector2f(100, 100));
  square.setFillColor(sf::Color::Black);
  square.setPosition(250, 300);

  auto point1 = square.getTransform().transformPoint(square.getPoint(0));
  auto point2 = square.getTransform().transformPoint(square.getPoint(1));
  auto point3 = square.getTransform().transformPoint(square.getPoint(2));
  auto point4 = square.getTransform().transformPoint(square.getPoint(3));

  Vector2f offset(square.getSize().x / 2.0, square.getSize().y / 2.0);

  auto newSize = [](Vector2f vector) { return Vector2f(vector.x * sin(45 * M_PI / 180.0f), vector.y * sin(45 * M_PI / 180.0f)); };

  auto getCorner = [](sf::RectangleShape x) { return x.getTransform().transformPoint(x.getPoint(1)); };
  auto newOffset = [](sf::RectangleShape x) { return Vector2f(x.getSize().x / 2.0, x.getSize().y / 2.0); };
  auto getCorner1 = [](sf::RectangleShape x) { return x.getTransform().transformPoint(x.getPoint(0)); };

  // cout << dot1.getRotation() << endl;
  auto offset1 = newOffset(square);

  sf::RectangleShape ltest(newSize(square.getSize()));
  ltest.setOrigin(ltest.getSize().x / 2, ltest.getSize().y / 2);
  ltest.setFillColor(sf::Color::Blue);
  ltest.rotate(-45);
  cout << " should be 315 " << ltest.getRotation() << endl;
  ltest.setPosition(getCorner1(square) + CalcOffset(ltest, offset));  // 315

  auto loffset = newOffset(ltest);

  sf::RectangleShape ltest2(newSize(ltest.getSize()));
  ltest2.setOrigin(ltest2.getSize().x / 2, ltest2.getSize().y / 2);
  ltest2.setFillColor(sf::Color::Blue);
  ltest2.rotate(ltest.getRotation() - 45);
  cout << ltest2.getRotation() << endl;
  ltest2.setPosition(getCorner1(ltest) + CalcOffset(ltest2, loffset));  // 270

  auto loffset1 = newOffset(ltest2);

  sf::RectangleShape ltest3(newSize(ltest2.getSize()));
  ltest3.setOrigin(ltest3.getSize().x / 2, ltest3.getSize().y / 2);
  ltest3.setFillColor(sf::Color::Blue);
  ltest3.rotate(ltest2.getRotation() - 45);
  cout << ltest3.getRotation() << endl;
  ltest3.setPosition(getCorner1(ltest2) + Vector2f(-loffset1.x, 0));  // 225

  auto loffset2 = newOffset(ltest3);

  sf::RectangleShape ltest4(newSize(ltest3.getSize()));
  ltest4.setOrigin(ltest4.getSize().x / 2, ltest4.getSize().y / 2);
  ltest4.setFillColor(sf::Color::Blue);
  ltest4.rotate(ltest3.getRotation() - 45);
  cout << ltest4.getRotation() << endl;
  ltest4.setPosition(getCorner1(ltest3) + Vector2f(-loffset2.x / sqrt(2), loffset2.y / sqrt(2)));  // 180

  auto loffset3 = newOffset(ltest4);

  sf::RectangleShape ltest5(newSize(ltest4.getSize()));
  ltest5.setOrigin(ltest5.getSize().x / 2, ltest5.getSize().y / 2);
  ltest5.setFillColor(sf::Color::Blue);
  ltest5.rotate(ltest4.getRotation() - 45);
  cout << ltest5.getRotation() << endl;
  ltest5.setPosition(getCorner1(ltest4) + Vector2f(0, loffset3.y));  // 135

  auto loffset4 = newOffset(ltest5);

  sf::RectangleShape ltest6(newSize(ltest5.getSize()));
  ltest6.setOrigin(ltest6.getSize().x / 2, ltest6.getSize().y / 2);
  ltest6.setFillColor(sf::Color::Blue);
  ltest6.rotate(ltest5.getRotation() - 45);
  cout << ltest6.getRotation() << endl;
  ltest6.setPosition(getCorner1(ltest5) + CalcOffset(ltest6, loffset4));  // 90

  auto loffset5 = newOffset(ltest6);

  sf::RectangleShape ltest7(newSize(ltest6.getSize()));
  ltest7.setOrigin(ltest7.getSize().x / 2, ltest7.getSize().y / 2);
  ltest7.setFillColor(sf::Color::Blue);
  ltest7.rotate(ltest6.getRotation() - 45);
  cout << ltest7.getRotation() << endl;
  ltest7.setPosition(getCorner1(ltest6) + Vector2f(loffset5.x, 0));  // 45

  auto loffset6 = newOffset(ltest7);

  sf::RectangleShape ltest8(newSize(ltest7.getSize()));
  ltest8.setOrigin(ltest8.getSize().x / 2, ltest8.getSize().y / 2);
  ltest8.setFillColor(sf::Color::Blue);
  ltest8.rotate(ltest7.getRotation() - 45);
  cout << ltest8.getRotation() << endl;
  ltest8.setPosition(getCorner1(ltest7) + Vector2f(loffset6.x / sqrt(2), -loffset6.y / sqrt(2)));  // 0

  sf::RenderWindow window1(sf::VideoMode(600, 400), "Pythagorean Tree");
  while (window1.isOpen()) {
    sf::Event event;
    while (window1.pollEvent(event)) {
      if (event.type == sf::Event::Closed)
        window1.close();
    }
    window1.clear(sf::Color::White);
    window1.draw(square);

    window1.draw(ltest);
    window1.draw(ltest2);
    window1.draw(ltest3);
    window1.draw(ltest4);
    window1.draw(ltest5);
    window1.draw(ltest6);
    window1.draw(ltest7);
    window1.draw(ltest8);
    window1.display();
  }

  return 0;
}

Vector2f CalcOffset(sf::RectangleShape square, Vector2f offset) {
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