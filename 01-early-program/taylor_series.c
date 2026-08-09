/*
 * taylor_series.c — Taylor series approximation of 1/(1-x)
 *
 * Approximates 1/(1-x) with the geometric series 1 + x + x^2 + ... for a
 * user-chosen number of terms, then reports the approximation, the exact
 * value, and the absolute error between them. The series converges only
 * for |x| < 1, so the domain is validated before any computation.
 */

#include <stdio.h>
#include <math.h>

int main(void) {
    double x;
    int terms;

    /* Reject values outside the convergence domain up front; x = 1 would
     * also divide by zero in the exact formula. */
    printf("Enter x: ");
    if (scanf("%lf", &x) != 1 || !isfinite(x) || fabs(x) >= 1.0) {
        printf("Invalid x: absolute value must be less than 1.\n");
        return 1;
    }

    printf("Enter number of terms: ");
    if (scanf("%d", &terms) != 1 || terms <= 0) {
        printf("Invalid terms: enter a positive integer.\n");
        return 1;
    }

    double approximation = 0.0;
    double term = 1.0;

    /* Build each term from the previous one with a running product —
     * one multiplication per iteration instead of a pow() call. */
    for (int i = 0; i < terms; ++i) {
        approximation += term;
        term *= x;
    }

    const double exact = 1.0 / (1.0 - x);
    const double absolute_error = fabs(exact - approximation);

    printf("Approximation: %.6f\n", approximation);
    printf("Exact: %.6f\n", exact);
    printf("Absolute error: %.6f\n", absolute_error);

    return 0;
}
