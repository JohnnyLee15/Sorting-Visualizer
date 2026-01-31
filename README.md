# Sorting Algorithm Visualizer

A simple C-based sorting algorithm visualizer built using **Raylib**.  
The project separates sorting logic from rendering and uses logged events
(swaps and comparisons) to animate algorithms step-by-step.

## Build

Requirements:
- clang
- raylib
- pkg-config

Build the project:
```bash
make
```

Run:
```bash
./main
```

Clean build artifacts:
```bash
make clean
```

## Structure

- `src/` – C source files
- `include/` – Header files
- `Makefile` – Build configuration

This project is intended for learning and experimentation.
