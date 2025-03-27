// Copyright 2024 Chris Lambert
#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>

namespace SB {
enum class Direction { Up,
                       Down,
                       Left,
                       Right };

class Sokoban : public sf::Drawable {
 public:
  Sokoban();
  // for test purposes
  explicit Sokoban(std::string filename);

  int getWidth() const { return width; }
  int getHeight() const { return height; }
  std::pair<int, int> playerLoc() const { return position; }
  void movePlayer(Direction d);
  bool isWon();

  friend std::istream& operator>>(std::istream& input, Sokoban& sokoban);

  ~Sokoban();

 protected:
  virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const {}

 private:
  std::string icons;
  std::string filename;
  int width;
  int height;
  std::vector<std::string> board;
  std::vector<sf::Sprite> sprites;
  std::pair<int, int> position;
  void setSprites();
  void restart();
  void playWin();
  sf::Texture* textures;
  sf::Text* text;
  std::map<Direction, sf::Texture> playerMap;
  Direction currentD;
  bool played;
  sf::Sound sound;
  sf::SoundBuffer soundBuffer;
};

}  // namespace SB
