// Copyright 2024 Chris Lambert
#include "RandWriter.hpp"
#include <algorithm>
#include <vector>
#include <random>
using std::cout;
using std::endl;

RandWriter::RandWriter(const string& text, size_t k) : _k(k), text(text) {
  for (size_t i = 0; i <= text.length() - k; ++i) {
    string kgram = text.substr(i, _k);
    char c = text[i + _k];
    kgramCount[kgram]++;
    charCount[kgram][c]++;
  }
}

int RandWriter::freq(const string& kgram) const {
  if (kgram.length() != _k)
    throw std::invalid_argument("Invalid kgram length");

  auto entry = kgramCount.find(kgram);

  if (entry != kgramCount.end())
    return entry->second;
  else
    return 0;
}

int RandWriter::freq(const string& kgram, char c) const {
  if (kgram.length() != _k)
    throw std::invalid_argument("Invalid kgram length");

  if (_k == 0) {
    return std::count(text.begin(), text.end(), c);
  }

  auto entry = charCount.find(kgram);

  if (entry != charCount.end()) {
    auto charEntry = entry->second.find(c);
    if (charEntry != entry->second.end())
      return charEntry->second;
  }
  return 0;
}

char RandWriter::kRand(const string& kgram) {
  if (kgram.length() != _k) {
    throw std::invalid_argument("Invalid kgram");
  }

  // Calculate the total frequency of characters following the given kgram
  int totalFreq = freq(kgram);

  if (totalFreq == 0) {
    throw std::invalid_argument("No characters following kgram");
  }

  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<int> dis(1, totalFreq);

  int count = dis(gen);  // Randomly selected count

  int charFreq = 0;

  for (const auto& submap : charCount[kgram]) {
    charFreq += submap.second;
    if (charFreq >= count) {
      return submap.first;
    }
  }

  throw std::runtime_error("Failed to generate character");
}

string RandWriter::generate(const string& kgram, size_t L) {
  if (kgram.length() != _k) {
    throw std::invalid_argument("kgram is not of length k");
  }
  string generatedText = kgram;
  for (size_t i = _k; i < L; ++i) {
    try {
      char nextChar = kRand(generatedText.substr(generatedText.length() - _k));
      generatedText.push_back(nextChar);
    } catch (std::invalid_argument& e) {
      auto circularString = [](string text, size_t order) {
        return text.substr(text.length() - order) + text.substr(0, order);
      };
      string subCircString = circularString(generatedText, _k);
      char nextChar = kRand(subCircString.substr(subCircString.length() - _k));
      generatedText.push_back(nextChar);
    }
  }

  return generatedText;
}

std::istream& operator>>(std::istream& is, RandWriter& rw) {
  std::string inputText;
  is >> inputText;
  rw.text = inputText;
  return is;
}

std::ostream& operator<<(std::ostream& os, const RandWriter& rw) {
  os << " Order: " << rw.orderK() << "\n"
     << "Alphabet: ";
  for (char c : rw.alphabet) {
    os << c << " ";
  }
  os << "\n";

  os << "K-gram Frequencies:\n";
  for (const auto& entry : rw.kgramCount) {
    os << entry.first << ": " << entry.second << "\n";
  }

  os << "K+1-gram Frequencies:\n";
  for (const auto& entry : rw.charCount) {
    for (const auto& subentry : entry.second) {
      os << entry.first << subentry.first << ": " << subentry.second << "\n";
    }
  }

  return os;
}
