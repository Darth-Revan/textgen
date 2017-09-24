/*
 * Copyright (c) 2017 Kevin Kirchner
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

/**
 * \file        markov.cpp
 * \brief       Source file implementing classes and functions for \p textgen
 * \author      Kevin Kirchner
 * \date        2017
 * \copyright   MIT License
 *
 * A source file implementing class and functions to use in \p textgen.
 */

#include "markov.h"
#include <fstream>
#include <sstream>

namespace textgen {

MarkovChain::MarkovChain(const std::string& filename) {
  std::ifstream in;
  in.open(filename, std::ios_base::in);
  if (!in.is_open()) {
    throw std::runtime_error("Could not open file for reading!");
  }
  buildChain(in);
  in.close();
}

bool MarkovChain::seedWithFile(const std::string& filename) {
  std::ifstream in;
  in.open(filename, std::ios_base::in);
  if (!in.is_open()) {
    return false;
  }
  buildChain(in);
  in.close();
  return true;
}

std::ostream& MarkovChain::printChain(std::ostream& stream) const {
  stream << "-------------------------\n";
  stream << "Generated Markov Chain:\n\n";
  for (const auto& e : TextChain) {
    stream << e.first << ": [";
    for (const auto& s : e.second) {
      stream << s;
      if (&s == &e.second.back())
        break;
      stream << ", ";
    }
    stream << "]\n";
  }
  return stream;
}

void MarkovChain::buildChain(std::ifstream& stream) {
  if (!stream.is_open()) {
    return;
  }

  std::string word_1 {}, word_2 {};
  stream >> word_1;
  while (stream >> word_2) {
    std::transform(word_1.begin(), word_1.end(), word_1.begin(), ::tolower);
    std::transform(word_2.begin(), word_2.end(), word_2.begin(), ::tolower);

    if (TextChain.find(word_1) == TextChain.end()) {
      TextChain[word_1] = std::vector<std::string> {};
    }

    // weighted by number of occurences
    TextChain[word_1].push_back(word_2);
    word_1 = word_2;
  }
}

std::string MarkovChain::generateText(unsigned int numWords) const {
  if (TextChain.empty() || numWords <= 0) {
    return std::string();
  }

  std::string word {};
  std::stringstream ss;

  // init random number generator
  std::random_device randDev;
  std::mt19937 gen(randDev());
  std::uniform_int_distribution<size_t> dist;

  // get random key to begin with
  auto it = TextChain.begin();
  std::advance(it, dist(gen) % TextChain.size());
  ss << it->first;
  word = it->first;
  size_t wordCount {1};

  std::vector<std::string> vec;
  while (wordCount < numWords) {
    if (TextChain.find(word) == TextChain.end()) {
      break;
    }
    vec = TextChain.at(word);
    auto c = vec.begin();
    std::advance(c, dist(gen) % vec.size());
    word = *c;
    ss << " " << word;
    ++wordCount;
  }
  return ss.str();
}

std::ostream& MarkovChain::generateText(std::ostream& stream,
                                        unsigned int numWords) const {
  stream << generateText(numWords);
  return stream;
}

} // namespace textgen
