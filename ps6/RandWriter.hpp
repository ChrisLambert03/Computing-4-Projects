// Copyright 2024 Chris Lambert
#pragma once
#include <iostream>
#include <string>
#include <map>

using std::map;
using std::string;

class RandWriter {
 public:
  friend std::istream& operator>>(std::istream& is, RandWriter& rw);
  friend std::ostream& operator<<(std::ostream& os, const RandWriter& rw);
  // Create a Markov model of order k from given text
  // Assume that text has length at least k.
  RandWriter(const string& text, size_t k);
  size_t orderK() const { return this->_k; }  // Order k of Markov model

  // Number of occurences of kgram in text
  // Throw an exception if kgram is not length k
  int freq(const string& kgram) const;
  // Number of times that character c follows kgram
  // if order=0, return num of times that char c appears
  // (throw an exception if kgram is not of length k)
  int freq(const string& kgram, char c) const;
  // Random character following given kgram
  // (throw an exception if kgram is not of length k)
  // (throw an exception if no such kgram)
  char kRand(const string& kgram);
  // Generate a string of length L characters by simulating a trajectory
  // through the corresponding Markov chain. The first k characters of
  // the newly generated string should be the argument kgram.
  // Throw an exception if kgram is not of length k.
  // Assume that L is at least k
  string generate(const string& kgram, size_t L);

 private:
  size_t _k;
  string text;
  const string alphabet = "ABCDEFGHIJHLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz ";
  map<string, int> kgramCount;
  map<string, map<char, int>> charCount;
};
// Overload the stream insertion operator << and display the internal state
// of the Markov model. Print out the order, alphabet, and the frequencies
// of the k-grams and k+1-grams
