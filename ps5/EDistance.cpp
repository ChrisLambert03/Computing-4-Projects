// Copyright 2024 Chris Lambert
#include "EDistance.hpp"

EDistance::EDistance(string a, string b) {
  if (b.length() > a.length()) {
    std::swap(a, b);
  }
  matrix.resize(a.size() + 2, std::vector<string>(b.size() + 2, "-"));

  for (size_t i = 1; i <= a.size(); ++i) {
    matrix[i][0] = a[i - 1];
  }
  for (size_t j = 1; j <= b.size(); ++j) {
    matrix[0][j] = b[j - 1];
  }
}
int EDistance::optDistance() {
  // 12 and 10 -> 10 , 8
  int count = 0;

  for (size_t i = matrix[0].size() - 1; i > 0; --i) {
    matrix[matrix.size() - 1][i] = std::to_string(count);
    count += 2;
  }
  count = 0;

  for (size_t i = matrix.size() - 1; i > 0; --i) {
    matrix[i][matrix[0].size() - 1] = std::to_string(count);
    count += 2;
  }

  for (size_t j = matrix.size() - 2; j > 0; --j) {
    for (size_t i = matrix[0].size() - 2; i > 0; --i) {
      auto& entry = matrix[j][i];

      auto a = matrix[j][0];
      auto b = matrix[0][i];

      auto x = std::stoi(matrix[j][i + 1]) + 2;
      auto y = std::stoi(matrix[j + 1][i]) + 2;
      auto z = std::stoi(matrix[j + 1][i + 1]) + 1;

      if (penalty(a[0], b[0])) {
        entry = std::to_string(min3(z, y, x));
      } else {
        entry = std::to_string(std::stoi(matrix[j + 1][i + 1]));
      }
    }
  }

  return stoi(matrix[1][1]);
}

int EDistance::calcDistance(size_t top, size_t left) {
  auto& entry = matrix[top][left];

  auto a = matrix[top][0];
  auto b = matrix[0][left];

  int x = calcDistance(top, left + 1) + 2;
  int y = calcDistance(top + 1, left) + 2;
  int z = calcDistance(top + 1, left + 1) + 1;

  if (penalty(a[0], b[0])) {
    entry = std::to_string(min3(z, y, x));
  } else {
    entry = matrix[top + 1][left + 1];
  }

  return stoi(entry);
}

string EDistance::alignment() {
  string alignment;

  alignment += "Edit Distance = " + std::to_string(optDistance()) + "\n";
  size_t i = 1, j = 1;
  while (i < matrix.size() - 1 && j < matrix[0].size() - 1) {
    auto a = matrix[i][0];
    auto b = matrix[0][j];
    int opt_current = std::stoi(matrix[i][j]);
    int opt_diagonal = std::stoi(matrix[i + 1][j + 1]);
    int opt_down = std::stoi(matrix[i + 1][j]);
    int opt_right = std::stoi(matrix[i][j + 1]);

    if (opt_current == opt_diagonal + (penalty(a[0], b[0]) ? 1 : 0)) {
      alignment += a + " " + b + " " + std::to_string(penalty(a[0], b[0])) + "\n";
      ++i;
      ++j;
    } else if (opt_current == opt_down + 2) {
      alignment += a + "   2\n";
      ++i;
    } else if (opt_current == opt_right + 2) {
      alignment += "  " + b + " 2\n";
      ++j;
    }
  }
  return alignment;
}
std::istream& operator>>(std::istream& input, EDistance& ed) {
  string a, b;
  getline(input, a);
  getline(input, b);
  ed = EDistance(a, b);

  return input;
}
