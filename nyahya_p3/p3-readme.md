# ECE250 Project 3: Hierarchical Text Classification

## Overview
This project implements a trie data structure designed for hierarchical text classification. The system classifies text into a hierarchy of categories, refining from broad base classes to more specific subclasses.

## Implementation Details
- Trie data structure (N-ary tree) where each level represents a more specific class in the hierarchy
- Root node represents the most general class
- Each subtree represents a refinement of its parent class
- Terminal nodes indicate final classification levels (internal nodes cannot be terminal)
- Fixed size of N = 15 (maximum children per node)

## Language Model Classifier
The trie stores only the class hierarchy. A language model classifier is provided to interact with the trie and perform actual text classification.

## Commands
| Command | Parameters | Description |
|---------|------------|-------------|
| LOAD    | filename   | Loads class hierarchy from file in comma-separated format |
| INSERT  | classification | Adds a new classification to the trie |
| CLASSIFY| input      | Classifies input text using the classifier and trie |
| ERASE   | classification | Removes a classification from the trie |
| PRINT   |            | Displays all classifications in comma-separated format |
| EMPTY   |            | Checks if the trie is empty |
| CLEAR   |            | Removes all classifications from the trie |
| SIZE    |            | Shows the number of classifications in the trie |
| EXIT    |            | Terminates the program |

## Runtime Analysis
- INSERT: O(n) where n is the number of classes in the classification
- CLASSIFY: O(N) where N is the number of classes in the trie
- ERASE: O(n) where n is the number of classes in the classification

## Exception Handling
The program handles illegal arguments (upper-case English letters) by throwing and catching an `illegal_exception` and outputting "illegal argument".

## Compilation
Use the provided Makefile:
```
make
```

## Testing
Test files are available in the format:
- Input: test01.in, test02.in, etc.
- Expected output: test01.out, test02.out, etc.
