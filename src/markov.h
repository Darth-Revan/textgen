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
 * \file        markov.h
 * \brief       Header file declaring classes and functions for \p textgen
 * \author      Kevin Kirchner
 * \date        2017
 * \copyright   MIT License
 *
 * A header file declaring class and functions to use in \p textgen.
 */

#ifndef TEXTGEN_MARKOV_H
#define TEXTGEN_MARKOV_H

#include <map>
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <random>

namespace textgen {

/// Main class for generating text with a Markov chain
class MarkovChain final {

public:
  /// Constructor of \p MarkovChain. Takes the path to a text file to use for
  /// generation.
  ///
  /// \param filename Path to the input file
  explicit MarkovChain(const std::string& filename);

  /// Copy constructor for \p Markov chain.
  ///
  /// \param other The instance to copy
  MarkovChain(const MarkovChain& other) = default;

  /// Destructor of \p Markov chain
  ~MarkovChain() {
    TextChain.clear();
  }

  /// Regenerate the Markov chain from the file \p filename. Only required if
  /// you want to reuse the object with a different file. Returns a boolean
  /// value indicating success or failure and writes a message to \p std::cerr
  /// if something goes wrong.
  ///
  /// \param filename Path to the input file
  /// \return \p true on success, \p false otherwise
  bool seedWithFile(const std::string& filename);

  /// Generate random text using the file read before and return the random
  /// text inside a string.
  ///
  /// \param numWords Number of words of the generated text
  /// \return String containing random text
  std::string generateText(unsigned int numWords) const;

  /// Generates random text of \p numWords words and prints it to \p stream.
  ///
  /// \param stream The stream to write to
  /// \param numWords Number of words of the generated text
  /// \return The modified stream
  std::ostream& generateText(std::ostream& stream, unsigned int numWords) const;

  /// Returns the length of the generated Markov chain (which is the number of
  /// keys in the chain).
  ///
  /// \return Length of Markov chain
  constexpr size_t getChainLength() const {
    return TextChain.size();
  }

  /// Prints the generated Markov chain to \p stream.
  ///
  /// \param stream The stream to write to
  /// \return The modified stream
  std::ostream& printChain(std::ostream& stream) const;

  /// Overloads the stream operator to directly write the object to an output
  /// stream.
  ///
  /// \param stream The stream to write to
  /// \param chain The object to write
  /// \return The modified stream
  friend std::ostream& operator<< (std::ostream& stream, const MarkovChain& chain) {
    stream << "MarkovChain (Chain Length: " << chain.TextChain.size() << ")";
    return stream;
  }

private:
  /// The markov chain with suffixes and a list of prefixes
  std::map<std::string, std::vector<std::string>> TextChain;

  /// Constructs the Markov chain from the input stream \p stream.
  ///
  /// \param stream An open input stream
  void buildChain(std::ifstream& stream);

};

} // namespace textgen

#endif //TEXTGEN_MARKOV_H
