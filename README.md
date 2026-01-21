# ft_printf

This project was developed as part of the École 42 curriculum.

## Objective
The goal of this project is to reimplement the standard `printf` function in C,
with a focus on extensibility, correctness, and code structure.

## Design
The implementation is based on a modular architecture using a table of function
pointers to handle format specifiers. This design allows the behavior to be easily
extended and maintained.

## Features
- Support for standard `printf` format specifiers
- Implementation of multiple bonus flags
- Structured and extensible parsing logic

## Testing
The repository includes a small automated testing tool to validate the behavior
of the custom `printf` implementation against expected outputs.

## Technical stack
- C
- Variadic functions
- Function pointers
- Linux

## Notes
This project focuses on clean design and extensibility rather than minimal compliance
with the subject requirements.
