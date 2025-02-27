# ECE250 Project 2: Hashing

## Overview
This project implements a hash table data structure for storing simulated file blocks. Two collision resolution techniques are implemented:
1. Open addressing with double hashing
2. Separate chaining with ordered lists

## File Block Structure
Each file block contains:
- A unique integer ID (used as the key for hashing)
- A payload (char array up to 500 bytes)
- A checksum to verify data integrity

## Checksum Calculation
The checksum is calculated as:
```
C = (∑c_i from i=0 to 500) % 256
```
where c_i is the integer value of the i-th character in the payload.

## Hash Functions
- Primary Hash Function: h₁(k) = k mod m
  - m is the size of the hash table (a power of 2)
- Secondary Hash Function (for double hashing): h₂(k) = ⌊k/m⌋ mod m
  - If h₂(k) is even, add 1 to make it odd

## Commands
| Command | Parameters | Description |
|---------|------------|-------------|
| NEW     | N T        | Creates a hash table of size N with type T (0=open, 1=chaining) |
| STORE   | ID charstring | Stores file block with given ID and payload |
| SEARCH  | ID         | Searches for file block with specified ID |
| DELETE  | ID         | Removes file block with specified ID |
| CORRUPT | ID charstring | Corrupts an existing file block without updating checksum |
| VALIDATE| ID         | Verifies checksum of file block |
| PRINT   | i          | Prints ordered chain at index i (separate chaining only) |
| EXIT    |            | Terminates the program |

## Runtime Analysis
For both hashing types (assuming at most m collisions where m << T and m is O(1)):
- STORE: O(1)
- SEARCH: O(1)
- DELETE: O(1)

## Compilation
Use the provided Makefile:
```
make
```

## Testing
Test files are available in the format:
- Input: test01.in, test02.in, etc.
- Expected output: test01.out, test02.out, etc.
