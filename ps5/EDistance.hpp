// Copyright 2024 Chris Lambert
#pragma once
#include <string>
#include <vector>
#include <iostream>
using std::string;
using std::vector;

class EDistance {
 public:
  friend std::istream& operator>>(std::istream& input, EDistance& ed);

  auto& operator[](size_t index) {
    if (index >= 0 && index <= matrix.size())
      return matrix[index];
    else
      throw std::out_of_range("Out of Range Index");
  }

  EDistance() = default;
  EDistance(string, string);

  static int penalty(char a, char b) { return (a == b) ? 0 : 1; }
  static int min3(int a, int b, int c) { return std::min(std::min(a, b), c); }
  int optDistance();
  string alignment();

 private:
  vector<vector<string>> matrix;

  int calcDistance(size_t top, size_t left);
};
