# TD4M CPU Emulator

A modular emulator of the TD4M (TD4 Microcode) 4-bit processor with extended instruction set, built in C++.

## Overview

This project implements a fully functional emulator of the TD4M architecture — an enhanced version of the classic TD4 teaching CPU. The emulator features a modular design with separate components for registers, bitset operations, security functions, and core execution logic.

## Features

- **4-bit architecture** with 8-bit instruction words
- **Extended instruction set** beyond basic TD4
- **Modular design** (separate modules for registers, bitset, security)
- **Makefile build system** for easy compilation
- **Memory management** with save/load functionality
- **Security-related functions** (anti-debugging, integrity checks)

## Instruction Set (Extended)

The TD4M supports all standard TD4 instructions plus additional operations:

| Category | Instructions |
|----------|--------------|
| Data Movement | `MOV A, Im`, `MOV B, Im`, `MOV A, B`, `MOV B, A` |
| Arithmetic | `ADD A, Im`, `ADD B, Im` |
| I/O Operations | `IN A`, `IN B`, `OUT B`, `OUT Im` |
| Control Flow | `JMP Im`, `JNC Im` |
| Extended | `MOV X, Im`, `MOV Y, Im`, `LD A`, `LNC XY` |

## Project Structure
