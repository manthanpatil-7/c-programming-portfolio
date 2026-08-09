# Pointer Toolkit

## Overview

A collection of pointer-based array utilities — swap, min/max with output
pointers, in-place reversal, a max-element pointer finder, a
pass-by-value vs. pass-by-reference demonstration, and a sum computed with
pointer arithmetic only (no indexing) — plus a dynamic-array demo that
allocates with `malloc`, averages and reverses the values, and frees the
memory. The program verifies itself: `main()` prints an expected/actual line
for every function before running the interactive demo.

## Skills Demonstrated

- Pointers and pointer arithmetic
- Dynamic memory management (`malloc`/`free`, ownership discipline)
- Defensive programming (every function guards against `NULL` and invalid sizes)
- Self-testing program design (built-in expected vs. actual checks)

## Compile and Run

```bash
gcc -std=c11 -Wall -Wextra pointer_toolkit.c -o midcourse_program
./midcourse_program
```

## Example

```text
Pointer Toolkit
swap expected 20 10, actual 20 10
minMax expected 1 9, actual 1 9
reverse expected 5 4 3 2 1, actual 5 4 3 2 1
maxPtr expected 9, actual 9
value expected 5, actual 5
reference expected 6, actual 6
sum expected 20, actual 20
Dynamic array size: 5
Enter 5 integers: 3 7 1 9 4
Average: 4.80
Reversed: 4 9 1 7 3
```

Edge cases are handled without crashing: `NULL` array pointers return safely,
`maxPtr` returns `NULL` for invalid input, and a non-positive dynamic-array
size is rejected before any allocation.

## Design and Testing

Two design decisions shaped the file. First, every function validates its
pointers before dereferencing, so no combination of bad inputs can crash the
program. Second, `reverseArray()` reuses `swap()` with two walking pointers
instead of duplicating the exchange logic. Testing is built into the program
itself — each utility prints its expected and actual result side by side —
and in the course CI the same functions passed unit tests compiled with
AddressSanitizer and UndefinedBehaviorSanitizer.