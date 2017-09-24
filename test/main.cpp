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
 * \file        main.cpp
 * \brief       Main test file of \p textgen
 * \author      Kevin Kirchner
 * \date        2017
 * \copyright   MIT License
 *
 * Main source file for the tests of \p textgen using Catch.
 */

#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "markov.h"

using namespace textgen;

TEST_CASE("Copy constructor", "[markov]") {
  MarkovChain k("gone.txt");
  MarkovChain m(k);
  REQUIRE(k.getChainLength() == m.getChainLength());
}

TEST_CASE("Text Generation 'gone.txt'", "[markov]") {
  MarkovChain k("gone.txt");
  REQUIRE(k.getChainLength() > 0);
  auto text = k.generateText(20);
  auto text_2 = k.generateText(20);
  REQUIRE_FALSE(text.empty());
  REQUIRE_FALSE(text_2.empty());
  text = k.generateText(0);
  REQUIRE(text.empty());
}

TEST_CASE("Text Generation 'lorem_ipsum.txt'", "[markov]") {
  MarkovChain k("lorem_ipsum.txt");
  REQUIRE(k.getChainLength() > 0);
  auto text = k.generateText(20);
  auto text_2 = k.generateText(20);
  REQUIRE_FALSE(text.empty());
  REQUIRE_FALSE(text_2.empty());
  text = k.generateText(0);
  REQUIRE(text.empty());
}
