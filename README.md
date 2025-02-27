# ECE250: Algorithms and Data Structures

This repository contains implementations of various data structures and algorithms completed for the ECE250 course. Each project focuses on different fundamental computer science concepts with practical implementations in C++.

## Project Overview

### [Project 0: Potential Field Navigation](./p0/)
- **Focus**: Dynamically allocated 2D arrays, basic object-oriented design
- **Application**: Robot navigation using potential fields
- **Key Concepts**:
  - Attractive and repulsive forces for path planning
  - Dynamic memory allocation and management
  - Coordinate system representation

### [Project 1: Work Stealing](./p1/)
- **Focus**: Double-ended queue (deque) implementation with dynamic resizing
- **Application**: Simulated multi-core CPU task scheduling
- **Key Concepts**:
  - Work distribution and load balancing
  - Task stealing algorithm
  - Dynamic array resizing

### [Project 2: Hashing](./p2/)
- **Focus**: Hash table implementation with two collision resolution techniques
- **Application**: File block storage and retrieval
- **Key Concepts**:
  - Open addressing with double hashing
  - Separate chaining with ordered lists
  - Checksum calculation for data integrity

### [Project 3: Hierarchical Text Classification](./p3/)
- **Focus**: Trie data structure
- **Application**: Text classification with hierarchical categories
- **Key Concepts**:
  - N-ary tree implementation
  - Language model integration
  - Classification refinement

### [Project 4: Graphs](./p4/)
- **Focus**: Graph implementation with weighted, undirected edges
- **Application**: Multi-relational entity representation
- **Key Concepts**:
  - Entity-relationship modeling
  - Path finding algorithms
  - Graph traversal operations

## Common Project Requirements

All projects adhere to the following requirements:
- Object-oriented design principles
- Proper encapsulation (private data members, public services)
- Memory leak prevention (validated with Valgrind)
- Command-line interface for testing
- Runtime analysis

## Tools and Technologies

- **Language**: C++
- **Build System**: Make (via provided Makefiles)
- **Testing**: Custom test cases via input/output files
- **Debugging**: gdb, Valgrind
- **Environment**: eceUbuntu server

## Getting Started

Each project directory contains:
- Source code files (.cpp, .h)
- A Makefile for compilation
- A README.md with specific project details
- Test input (.in) and expected output (.out) files

To compile any project:
```bash
cd projectX
make
```

To run with test input:
```bash
./a.out < testXX.in
```

## Author

Nouran Yahya
