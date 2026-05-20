# Gator AVL

A C++ command-line AVL tree project for storing and managing student names and 8-digit IDs.

The program reads commands from standard input, validates names and IDs, and supports insertion, removal, search, traversals, level count, and inorder-index removal.

## Files

- `src/main.cpp`: command parser and program entry point.
- `src/AVL.h`: AVL tree implementation.
- `test/test.cpp`: Catch2 test file from the project submission.
- `CMakeLists.txt`: CMake configuration based on the Catch2 project template.

## Build With CMake

```bash
cmake -S . -B build
cmake --build build
```

## Run

```bash
./build/Main
```

The first input line should be the number of commands to process.

## Example

```text
5
insert "Brandon" 45679999
insert "Brian" 35459999
printInorder
search 45679999
printLevelCount
```

## Direct Compile

```bash
g++ -std=c++14 -I src src/main.cpp -o Main
```
