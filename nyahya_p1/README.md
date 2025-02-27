# ECE250 Project 1: Work Stealing

## Overview
This project implements a work-stealing algorithm to simulate a multi-core CPU environment. The core data structure is a double-ended queue (deque) that represents the task queue for each CPU core. The system distributes tasks to workers with the least work and allows idle workers to "steal" tasks from busy ones.

## Implementation Details
- Custom deque class implemented as a resizable array of integers
- Each integer represents a task ID to be processed
- Dynamic resizing:
  - When size reaches capacity: Double the capacity
  - When size drops to 1/4 of capacity: Halve the capacity
  - Minimum capacity: 2

## Work Stealing Algorithm
- New tasks are assigned to the worker with the least work
- Workers process tasks from the front of their queue
- If a worker runs out of tasks, it finds the worker with the most tasks and steals a task from the back of its queue
- This approach ensures even distribution of work and maximum utilization of workers

## Commands
| Command | Parameters | Description |
|---------|------------|-------------|
| ON      | N          | Creates a new CPU instance with N cores (0 to N-1) |
| SPAWN   | P_ID       | Creates a new task with ID P_ID, assigns to core with least work |
| RUN     | C_ID       | Core C_ID runs its next task or steals from the busiest core |
| SLEEP   | C_ID       | Distributes tasks from core C_ID to others with least work |
| SHUTDOWN|            | Removes all remaining tasks from all queues |
| SIZE    | C_ID       | Shows number of tasks in core C_ID's queue |
| CAPACITY| C_ID       | Shows capacity of core C_ID's queue |
| EXIT    |            | Terminates the program |

## Runtime Analysis
- RUN command: O(1) when no resizing occurs
- SPAWN command: O(C) worst-case where C is queue capacity

## Compilation
Use the provided Makefile:
```
make
```

## Testing
Test files are available in the format:
- Input: test01.in, test02.in, etc.
- Expected output: test01.out, test02.out, etc.
