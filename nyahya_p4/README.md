# ECE250 Project 4: Graphs

## Overview
This project implements a graph data structure to store a weighted, undirected graph and perform various lookup operations. The implementation specifically handles multi-relational graphs where nodes represent entities and edges represent relationships between entities.

## Multi-Relational Graph
- Nodes represent entities with:
  - Labels (strings) indicating entity type
  - Unique identifiers (strings)
  - Names (strings, not necessarily unique)
- Edges represent relationships with:
  - Labels (strings) indicating relationship type
  - Weights (positive doubles) indicating relationship strength

## Input Files
The system processes two types of input files:
1. Entity files: Define nodes with format `string_ID string_name string_type`
2. Relationship files: Define edges with format `string_sourceID string_label string_destinationID double_weight`

## Commands
| Command | Parameters | Description |
|---------|------------|-------------|
| LOAD    | Filename type | Loads dataset (entities or relationships) into the graph |
| RELATIONSHIP | Source_ID label Destination_ID weight | Inserts a new edge |
| ENTITY  | ID name type | Inserts a new entity (node) |
| PRINT   | ID          | Shows all vertices adjacent to the specified vertex |
| DELETE  | ID          | Removes a vertex and all its edges |
| PATH    | ID_1 ID_2   | Finds highest-weight path between two vertices |
| HIGHEST |             | Finds two vertices with the highest-weight path between them |
| FINDALL | Field_type Field_string | Lists entities with the specified field value |
| EXIT    |             | Terminates the program |

## Exception Handling
For specific commands (PRINT, DELETE, PATH), the program handles invalid input by throwing and catching an `illegal_exception` and outputting "illegal argument".

## Runtime Analysis
- PATH algorithm: O((|E|+|V|)log(|V|)) where |E| is the number of edges and |V| is the number of vertices

## STL Limitations
The implementation is restricted to using only:
- `<vector>`
- `<algorithm>`
- `<tuple>`

## Compilation
Use the provided Makefile:
```
make
```

## Testing
Test files are available in the format:
- Input: test01.in, test02.in, etc.
- Expected output: test01.out, test02.out, etc.
