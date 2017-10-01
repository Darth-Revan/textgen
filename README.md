# textgen

Random text generator based on Markov chains written in C++11

## Building

In order to build the project, you will need `cmake` and C++11-compliant compiler (e.g. GCC or Clang). The command line interface is based on the header-only library [TCLAP](http://tclap.sourceforge.net/), so the headers of this awesome library need to be installed on your system.

To build the project, change to the project directory, create a new build directory (not required, but I strongly recommend to make out-of-source builds) and compile the tool:

```bash
cd /path/to/textgen
mkdir build && cd build
cmake ..
make textgen
```

The software has only been tested on Linux, but as I only used the standard library and `TCLAP` it should also work on Windows or Mac OS.

## Usage

To use the tool to generate some text, you need to pass some text file to the program. This text will be used to build the Markov chain. Additionally you may choose the maximum number of words to generate (Default: 20), like this:

```bash
# Generate 20 random words from Hamlet
textgen -f hamlet.txt

# Generate 1000 random words from Tolstoy's 'War and Peace'
textgen -f tolstoy.txt -n 1000
```

## Example Files

The project contains some example text files in the sub-directory `rsrc`. These can be used for testing the program or playing around. The files include the first paragraph of the latin dummy text "Lorep Ipsum" and the free-to-use versions of Shakespeare's "Hamlet" and Leo Tolstoy's "War and Peace" from [Project Gutenberg](https://www.gutenberg.org/ ).

## License

This software is provided under the terms of the MIT License. See the file `LICENSE` for more information.