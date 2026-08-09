# Taylor Series Approximator

## Overview

Approximates `1/(1-x)` using its Taylor series `1 + x + x² + x³ + …` for a
user-chosen number of terms, then compares the approximation against the
exact value and reports the absolute error. Written in Week 2 of the course
(loops unit), before functions were introduced — the entire program lives in
`main()` by design.

## Skills Demonstrated

- Loops and accumulator variables
- Floating-point math and formatted output
- Input validation (domain check `|x| < 1`, positive term count)
- Error analysis (comparing an approximation against the closed form)

## Compile and Run

```bash
gcc -std=c11 -Wall -Wextra taylor_series.c -o early_program -lm
./early_program
```

## Example

Normal case:

```text
Enter x: 0.5
Enter number of terms: 4
Approximation: 1.875000
Exact: 2.000000
Absolute error: 0.125000
```

Edge case — the series only converges for `|x| < 1`, so invalid input is
rejected before any math runs:

```text
Enter x: 1.2
Invalid x: absolute value must be less than 1.
```

## What I Learned

Each term is built from the previous one with a running product
(`term *= x`) instead of calling `pow()` every iteration — the loop does one
multiplication per term. The domain check matters twice: the series diverges
for `|x| ≥ 1`, and the exact formula `1/(1-x)` would divide by zero at
`x = 1`, so the program validates before computing anything.