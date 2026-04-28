# Page Replacement Simulator
## Overview
Page Replacement Simulator is a visual learning tool designed to demonstrate CPU memory management techniques used in operating systems. It simulates classic page replacement algorithms with a step-by-step output and an interactive GUI to help understand how virtual memory works.

## Problem Statement
In operating systems, when a page fault occurs and memory is full, the OS must decide WHICH page to remove. Poor replacement decisions lead to:

- Excessive page faults
- Increased memory access time
- Degraded system performance
- Thrashing in worst cases

## Proposed Solution
This simulator implements four well-known page replacement algorithms:

- **FIFO** — Replaces the page that has been in memory the longest
- **LRU** — Replaces the page that was least recently used
- **LFU** — Replaces the page with the lowest access frequency
- **Optimal** — Replaces the page that will not be used for the longest future time

Each algorithm is compared side by side to understand their efficiency.

## Working of the Algorithms

1. User provides a page reference string and number of frames
2. Simulator loads pages into frames one by one
3. On each step, it checks for a page hit or page fault
4. On a fault, the chosen algorithm decides which page to replace
5. Final summary shows total faults, hits, and hit rate

## System Architecture

- **Backend:** C (Page replacement logic for all 4 algorithms)
- **Frontend:** Python Tkinter (Dark themed GUI)
- **Input:** Page string and frame count entered via UI
- **Output:** Step-by-step fault/hit trace and summary statistics

## Features

- Four page replacement algorithms in one tool
- Step-by-step hit/fault trace output
- Summary with fault count, hit count, and hit rate
- Dark themed interactive GUI
- Dynamic window resizing
- Subprocess-based backend integration
