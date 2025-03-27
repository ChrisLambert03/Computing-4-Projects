// Copyright 2024 Chris Lambert
#include "Sokoban.hpp"

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

using sf::Image;
using sf::Sprite;
using sf::Texture;
using std::cin;
using std::getline;
using std::pair;
using std::string;

using std::cout;
using std::endl;

SB::Sokoban::Sokoban() {
  played = false;
  currentD = Direction::Down;

  cin >> filename;
  std::ifstream file(filename);

  if (!file.is_open()) {
    std::cerr << "Failed to open file." << std::endl;
    exit(1);
  }

  string line;
  getline(file, line);
  std::istringstream iss(line);
  iss >> this->height >> this->width;

  // initialize vector size
  this->board.resize(height);

  for (int i = 0; i < height; i++) {
    std::getline(file, line);
    board[i] = line;
  }

  // up down left right
  Image image1, image2, image3, image4, image5, image6, image7, image8;
  image1.loadFromFile("player_08.png");
  image2.loadFromFile("player_05.png");
  image3.loadFromFile("player_20.png");
  image4.loadFromFile("player_17.png");
  image5.loadFromFile("block_06.png");
  image6.loadFromFile("crate_03.png");
  image7.loadFromFile("ground_01.png");
  image8.loadFromFile("ground_04.png");

  textures = new Texture[8];
  text = new sf::Text[1];

  // up down left right
  textures[0].loadFromImage(image1);
  textures[1].loadFromImage(image2);
  textures[2].loadFromImage(image3);
  textures[3].loadFromImage(image4);
  // wall box empty storage
  textures[4].loadFromImage(image5);
  textures[5].loadFromImage(image6);
  textures[6].loadFromImage(image7);
  textures[7].loadFromImage(image8);

  playerMap[Direction::Up] = textures[0];
  playerMap[Direction::Down] = textures[1];
  playerMap[Direction::Left] = textures[2];
  playerMap[Direction::Right] = textures[3];

  setSprites();

  sf::Font font;
  if (!font.loadFromFile("Noto Mono for Powerline.ttf")) {
    std::cerr << "Could not Open Font" << endl;
  }

  // Create a text which uses our font
  sf::Text text1;
  text1.setFont(font);
  text1.setCharacterSize(50);
  text1.setStyle(sf::Text::Regular);
  text1.setString("You Win!");
  sf::FloatRect textRect = text1.getLocalBounds();
  text1.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
  text1.setPosition(width * 64 / 2, height * 64 / 2);
  this->text[0] = text1;

  sf::RenderWindow window(sf::VideoMode(width * 64, height * 64), "Sokoban");
  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed)
        window.close();
    }
    window.clear(sf::Color::Black);

    for (auto i = sprites.begin(); i != sprites.end(); ++i) {
      window.draw(*i);
    }
    setSprites();
    window.display();

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {
      restart();
    }
    if (isWon()) {
      window.draw(text[0]);
      window.display();
      continue;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
      movePlayer(Direction::Up);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
      movePlayer(Direction::Left);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
      movePlayer(Direction::Down);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
      movePlayer(Direction::Right);
    }
  }
}
SB::Sokoban::Sokoban(std::string filename) : filename(filename) {
  std::ifstream file(filename);

  if (!file.is_open()) {
    std::cerr << "Failed to open file." << std::endl;
    exit(1);
  }

  string line;
  getline(file, line);
  std::istringstream iss(line);
  iss >> this->width >> this->height;

  // initialize vector size
  this->board.resize(height);

  for (int i = 0; i < height; i++) {
    std::getline(file, line);
    board[i] = line;
  }

  // up down left right
  Image image1, image2, image3, image4, image5, image6, image7, image8;
  image1.loadFromFile("player_08.png");
  image2.loadFromFile("player_05.png");
  image3.loadFromFile("player_20.png");
  image4.loadFromFile("player_17.png");
  image5.loadFromFile("block_06.png");
  image6.loadFromFile("crate_03.png");
  image7.loadFromFile("ground_01.png");
  image8.loadFromFile("ground_04.png");

  textures = new Texture[8];
  text = new sf::Text[1];

  // up down left right
  textures[0].loadFromImage(image1);
  textures[1].loadFromImage(image2);
  textures[2].loadFromImage(image3);
  textures[3].loadFromImage(image4);
  // wall box empty storage
  textures[4].loadFromImage(image5);
  textures[5].loadFromImage(image6);
  textures[6].loadFromImage(image7);
  textures[7].loadFromImage(image8);

  playerMap[Direction::Up] = textures[0];
  playerMap[Direction::Down] = textures[1];
  playerMap[Direction::Left] = textures[2];
  playerMap[Direction::Right] = textures[3];

  setSprites();

  sf::Font font;
  if (!font.loadFromFile("Noto Mono for Powerline.ttf")) {
    std::cerr << "Could not Open Font" << endl;
  }

  // Create a text which uses our font
  sf::Text text1;
  text1.setFont(font);
  text1.setCharacterSize(50);
  text1.setStyle(sf::Text::Regular);
  text1.setString("You Win!");
  sf::FloatRect textRect = text1.getLocalBounds();
  text1.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
  text1.setPosition(width * 64 / 2, height * 64 / 2);
  this->text[0] = text1;
}
// destructor
SB::Sokoban::~Sokoban() {
  delete[] textures;
  delete[] text;
}
//
void SB::Sokoban::movePlayer(Direction d) {
  currentD = d;
  auto swap = [](auto& x, auto& y) {
    auto temp = x;
    x = y;
    y = temp;
  };
  // first is down, second is across
  auto& location = board[playerLoc().first][playerLoc().second];
  auto& above = board[playerLoc().first - 1][playerLoc().second];
  auto& below = board[playerLoc().first + 1][playerLoc().second];
  auto& left = board[playerLoc().first][playerLoc().second - 1];
  auto& right = board[playerLoc().first][playerLoc().second + 1];

  auto& above2 = board[playerLoc().first - 2][playerLoc().second];
  auto& below2 = board[playerLoc().first + 2][playerLoc().second];
  auto& left2 = board[playerLoc().first][playerLoc().second - 2];
  auto& right2 = board[playerLoc().first][playerLoc().second + 2];
  // based on direction, look to blocks ahead and determine proper mvoement
  switch (d) {
    case Direction::Up:

      if (above == '.') {
        swap(location, above);
        position.first -= 1;
      } else if (above == 'A') {
        if (above2 == 'a') {
          above2 = '1';
          above = '.';
          swap(location, above);
          position.first += 1;
        } else if (above2 == '.') {
          swap(above2, above);
          swap(location, above);
        }
      }
      while ((sf::Keyboard::isKeyPressed(sf::Keyboard::W))) {
      }
      break;
    case Direction::Down:

      if (below == '.') {
        swap(location, below);
        position.first += 1;
      } else if (below == 'A') {
        if (below2 == 'a') {
          below2 = '1';
          below = '.';
          swap(location, below);
          position.first += 1;
        } else if (below2 == '.') {
          swap(below2, below);
          swap(location, below);
        }
      }
      while ((sf::Keyboard::isKeyPressed(sf::Keyboard::S))) {
      }
      break;
    case Direction::Left:

      if (left == '.') {
        swap(location, left);
        position.second -= 1;
      } else if (left == 'A') {
        if (left2 == 'a') {
          left2 = '1';
          left = '.';
          swap(location, left);
          position.second -= 1;
        } else if (left2 == '.') {
          swap(left2, left);
          swap(location, left);
          position.second -= 1;
        }
      }

      while ((sf::Keyboard::isKeyPressed(sf::Keyboard::A))) {
      }
      break;
    case Direction::Right:

      if (right == '.') {
        swap(location, right);
        position.second += 1;
      } else if (right == 'A') {
        if (right2 == 'a') {
          right2 = '1';
          right = '.';
          swap(location, right);
          position.second += 1;
        } else if (right2 == '.') {
          swap(right2, right);
          swap(location, right);
          position.second += 1;
        }
      }
      while ((sf::Keyboard::isKeyPressed(sf::Keyboard::D))) {
      }
      break;
    default:
      break;
  }
}

void SB::Sokoban::restart() {
  played = false;
  currentD = Direction::Down;
  sprites.clear();

  std::ifstream file(filename);

  if (!file.is_open()) {
    std::cerr << "Failed to open file." << std::endl;
    exit(1);
  }

  string line;
  getline(file, line);
  std::istringstream iss(line);
  iss >> this->width >> this->height;

  // initialize vector size
  this->board.clear();
  this->board.resize(height);

  for (int i = 0; i < height; i++) {
    std::getline(file, line);
    board[i] = line;
  }
  setSprites();
}

bool SB::Sokoban::isWon() {
  // look for an 'a' on the board
  for (auto i : board) {
    for (auto j : i) {
      if (j == 'a')
        return false;
    }
  }
  return true;
}

/*
texture mappings:
0  - up
1 - down
2 - left
3 - right

4 - wall
5 - box
6 - empty (tile)
7 - storage (border tile)
*/

void SB::Sokoban::setSprites() {
  double cordinates[] = {0.0, 0.0};

  Sprite block;

  for (int i = 0; i < height; i++) {
    std::string row = board[i];
    for (int j = 0; j < width; j++) {
      char icon = row[j];
      block.setPosition(cordinates[0], cordinates[1]);

      if (icon == '#') {  // a wall
        block.setTexture(textures[4]);
      } else if (icon == '@') {  // player position, draw tile then player
        block.setTexture(textures[6]);
        this->sprites.push_back(block);
        block.setTexture(playerMap[currentD]);
        position.first = i;
        position.second = j;
      } else if (icon == '.') {  // empty space, draw a wile
        block.setTexture(textures[6]);
      } else if (icon == 'A') {  // A box
        block.setTexture(textures[5]);
      } else if (icon == 'a') {  // storage location
        block.setTexture(textures[7]);
      } else if (icon == '1') {  // box already in storage location
        block.setTexture(textures[5]);
      }

      this->sprites.push_back(block);
      cordinates[0] += 64;
    }
    cordinates[1] += 64;
    cordinates[0] = 0;
  }
}

namespace SB {
std::istream& operator>>(std::istream& input, Sokoban& sokoban) {
  input >> sokoban.filename;
  return input;
}
}  // namespace SB
