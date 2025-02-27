# ECE250 Project 0: Potential Field Navigation

## Overview
This project implements a 2D grid-based potential field navigation system for robot path planning. The implementation uses dynamically allocated arrays to represent the environment where:
- Goals exert attractive forces (negative potential)
- Obstacles exert repulsive forces (positive potential)
- Robots navigate by moving toward the lowest potential field

## Implementation Details
- Coordinate system with origin (0,0) at the top-left corner
- Potential calculations use the formula: 
  ```
  P = < -K/√((x-xG)² + (y-yG)²), -K/√((x-xG)² + (y-yG)²) >
  ```
  where K is a constant defined in the program
- The total potential at any point is the sum of all potentials from goals and obstacles
- If a robot and a goal/obstacle occupy the same position, the potential is zero

## Commands
| Command | Parameters | Description |
|---------|------------|-------------|
| CREATE  | N M        | Creates a new N×M map with all potentials set to ⟨0,0⟩ |
| POINT   | T X Y      | Adds a goal (T='G') or obstacle (T='O') at position (X,Y) |
| MOVE    | X Y        | Outputs the potential field at position (X,Y) |
| CLEAR   |            | Removes all obstacles and goals, resets potentials to ⟨0,0⟩ |
| UPDATE  | K          | Changes the K value used in potential calculations |
| EXIT    |            | Terminates the program |

## Runtime Analysis
- The MOVE command has a runtime of O(N×M)

## Compilation
Use the provided Makefile:
```
make
```

## Testing
Test files are available in the format:
- Input: test01.in, test02.in, etc.
- Expected output: test01.out, test02.out, etc.
