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
 * \brief       Main file of \p textgen
 * \author      Kevin Kirchner
 * \date        2017
 * \copyright   MIT License
 *
 * Main source file of \p textgen.
 */

#include <tclap/CmdLine.h>
#include "markov.h"

int main(int argc, const char* argv[]) {
  try {
    TCLAP::CmdLine cmd("Random text generator based on Markov chains written in C++14", ' ', TEXTGEN_VERSION);
    TCLAP::ValueArg<std::string> fileArg("f", "file", "The file to use for the Markov chain", true, "", "string");
    TCLAP::ValueArg<unsigned int> numArg("n", "num", "The number of words to generate (Default: 20)", false, 20, "number");
    TCLAP::SwitchArg printArg("p", "print", "Print the constructed Markov chain instead of generating text");

    cmd.add(fileArg);
    cmd.add(numArg);
    cmd.add(printArg);
    cmd.parse(argc, argv);

    if (fileArg.getValue().empty()) {
      std::cerr  << "Argument for '-f' must not be empty!\n";
      return 1;
    }
    try {
      textgen::MarkovChain chain(fileArg.getValue());
      if (printArg.getValue()) {
        chain.printChain(std::cout);
      } else {
        chain.generateText(std::cout, numArg.getValue());
      }
    } catch (const std::runtime_error& ex) {
      std::cerr << ex.what() << "\n";
      return 1;
    }
  } catch (const TCLAP::ArgException& e) {
    std::cerr << e.error() << "\n";
    return 1;
  }
  return 0;
}
