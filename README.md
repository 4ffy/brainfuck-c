# Brainfuck Interpreter

A simple [Brainfuck](https://en.wikipedia.org/wiki/Brainfuck) interpreter
written in C. It takes a naive approach without any fancy optimization.

Source code is given from a file given at the command line, and the bit width
of the cells can also be specified (e.g. `./brainfuck hello.bf 16`). The
interpreter detects whether a program takes input and will only prompt for
input if necessary. Arbitrary cell sizes are supported up to at least 32
bytes.

## Caveats
Every Brainfuck interpreter has its idiosyncrasies. Here's some of the
relevant ones for this program.
- Cells wrap around when they go below zero or above the max cell size.
- Cells are set to 0 when a `,` operation is read and there is no input left.
- Input strings are given on a single line and terminated by a newline, which
  is not included when passed to the interpreter.
