/*
 * pointer_toolkit.c — pointer-based array utilities with built-in checks
 *
 * A small collection of pointer-driven routines: swapping, min/max through
 * output parameters, in-place reversal, max-element lookup, a
 * pass-by-value vs. pass-by-reference demonstration, and a sum computed
 * with pointer arithmetic alone. main() doubles as a test driver: it
 * prints an expected/actual line for every routine, then runs an
 * interactive dynamic-array demo backed by malloc/free.
 *
 * Every routine validates its pointers before dereferencing, so invalid
 * input degrades to a safe no-op, a zero result, or a NULL return instead
 * of undefined behavior.
 */

#include <stdio.h>
#include <stdlib.h>

/* Exchanges the values at a and b; no-op if either pointer is NULL. */
void swap(int *a, int *b);

/* Writes the smallest and largest of arr[0..n-1] through the output
 * pointers; no-op on NULL pointers or non-positive n. */
void minMax(const int *arr, int n, int *minOut, int *maxOut);

/* Reverses arr[0..n-1] in place; no-op for NULL or fewer than two items. */
void reverseArray(int *arr, int n);

/* Returns a pointer to the largest element, or NULL on invalid input. */
int *maxPtr(int *arr, int n);

/* Receives a copy of n — the caller's variable cannot change. */
void addOneValue(int n);

/* Receives the caller's address and increments the original value. */
void addOneReference(int *n);

/* Sums arr[0..n-1] using pointer traversal only; 0 on invalid input. */
int sumWithPointers(const int *arr, int n);

/* Interactive demo: allocates an n-element array, reports the average,
 * reverses it, and releases the memory. Returns a process exit status. */
int runDynamicArrayDemo(void);

int main(void)
{
    printf("Pointer Toolkit\n");
    int x = 10, y = 20;
    int data[] = {5, 2, 8, 1, 9, 3};
    int minimum = 0, maximum = 0;
    int reverse_data[] = {1, 2, 3, 4, 5};
    int max_data[] = {3, 7, 1, 9, 4};
    int number = 5;

    swap(&x, &y);
    printf("swap expected 20 10, actual %d %d\n", x, y);
    minMax(data, 6, &minimum, &maximum);
    printf("minMax expected 1 9, actual %d %d\n", minimum, maximum);
    reverseArray(reverse_data, 5);
    printf("reverse expected 5 4 3 2 1, actual");
    for (int i = 0; i < 5; i++) printf(" %d", reverse_data[i]);
    printf("\n");

    int *largest = maxPtr(max_data, 5);
    printf("maxPtr expected 9, actual %d\n", largest == NULL ? 0 : *largest);
    addOneValue(number);
    printf("value expected 5, actual %d\n", number);
    addOneReference(&number);
    printf("reference expected 6, actual %d\n", number);
    printf("sum expected 20, actual %d\n",
           sumWithPointers((int[]){2, 4, 6, 8}, 4));

    return runDynamicArrayDemo();
}

void swap(int *a, int *b)
{
    if (a == NULL || b == NULL) return;

    int temporary = *a;
    *a = *b;
    *b = temporary;
}

void minMax(const int *arr, int n, int *minOut, int *maxOut)
{
    if (arr == NULL || n <= 0 || minOut == NULL || maxOut == NULL) return;

    *minOut = *arr;
    *maxOut = *arr;
    for (const int *current = arr + 1; current < arr + n; current++)
    {
        if (*current < *minOut) *minOut = *current;
        if (*current > *maxOut) *maxOut = *current;
    }
}

void reverseArray(int *arr, int n)
{
    if (arr == NULL || n <= 1) return;

    /* Two pointers walk toward each other, reusing swap() for the exchange. */
    int *left = arr;
    int *right = arr + n - 1;
    while (left < right)
    {
        swap(left, right);
        left++;
        right--;
    }
}

int *maxPtr(int *arr, int n)
{
    if (arr == NULL || n <= 0) return NULL;

    int *largest = arr;
    for (int *current = arr + 1; current < arr + n; current++)
    {
        if (*current > *largest) largest = current;
    }
    return largest;
}

void addOneValue(int n)
{
    /* Pass-by-value demonstration: only the local copy changes. */
    n++;
    (void)n;
}

void addOneReference(int *n)
{
    if (n != NULL) (*n)++;
}

int sumWithPointers(const int *arr, int n)
{
    if (arr == NULL || n <= 0) return 0;

    int sum = 0;
    const int *end = arr + n;
    /* p++ advances by sizeof(int), so it reaches the next array element. */
    for (const int *p = arr; p < end; p++) sum += *p;
    return sum;
}

int runDynamicArrayDemo(void)
{
    int n;
    int status = 0;
    long long sum = 0;

    printf("Dynamic array size: ");
    if (scanf("%d", &n) != 1 || n <= 0)
    {
        printf("Invalid size.\n");
        return 1;
    }

    int *values = malloc((size_t)n * sizeof(int));
    if (values == NULL)
    {
        printf("Memory allocation failed.\n");
        return 1;
    }

    printf("Enter %d integers: ", n);
    for (int i = 0; i < n; i++)
    {
        if (scanf("%d", &values[i]) != 1)
        {
            printf("Invalid array value.\n");
            status = 1;
            break;
        }
        sum += values[i];
    }

    if (status == 0)
    {
        printf("Average: %.2f\n", (double)sum / n);
        reverseArray(values, n);
        printf("Reversed:");
        for (int i = 0; i < n; i++) printf(" %d", values[i]);
        printf("\n");
    }

    /* Single owner: release the buffer and clear the pointer so the freed
     * memory cannot be reused by mistake. */
    free(values);
    values = NULL;
    return status;
}
