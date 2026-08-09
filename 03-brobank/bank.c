#include <stdio.h>
#include "bank.h"

/*
 * bank.c — implementation of the BroBank interface
 *
 * Organized in four sections: account operations, persistence and logging,
 * the sorted session statement, and display helpers. Function contracts
 * are documented in bank.h; comments here cover implementation details
 * only.
 */

/* ---- Account operations ---- */

void deposit(double *balance, double amount)
{
    if (balance == NULL || amount <= 0.0) return;
    (*balance) += amount;
}

int withdraw(double *balance, double amount)
{
    if (balance == NULL || amount <= 0.0 || amount > *balance) return 0;
    (*balance) -= amount;
    return 1;
}

/* ---- Persistence and logging ---- */

double loadBalance(void)
{
    double balance = 0.0;
    FILE *fp = fopen("brobank_data.txt", "r");

    /* A missing file is normal on the first run. */
    if (fp == NULL)
    {
        return 0.0;
    }

    /* A corrupt or negative stored value falls back to a fresh account. */
    if (fscanf(fp, "%lf", &balance) != 1 || balance < 0.0)
    {
        balance = 0.0;
    }
    fclose(fp);
    return balance;
}

void saveBalance(double balance)
{
    FILE *fp = fopen("brobank_data.txt", "w");

    if (fp == NULL)
    {
        printf("Error: could not save balance\n");
        return;
    }

    fprintf(fp, "%.2f\n", balance);
    fclose(fp);
}

void logTransaction(const char type[], double amount, double balance)
{
    /* Append mode preserves the history across runs; the compile-time
     * date stamps each record. */
    FILE *fp = fopen("transactions.txt", "a");

    if (fp == NULL)
    {
        printf("Error: could not log transaction\n");
        return;
    }

    fprintf(fp, "%s,%s,%.2f,%.2f\n", __DATE__, type, amount, balance);
    fclose(fp);
}

/* ---- Session statement ---- */

void bubbleSortFloats(double arr[], int n)
{
    if (arr == NULL || n <= 1) return;

    /* Each pass floats the largest remaining value to the end, so the
     * inner bound shrinks by one every pass. */
    for (int pass = 0; pass < n - 1; pass++)
    {
        int swapped = 0;
        for (int j = 0; j < n - 1 - pass; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                double temporary = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temporary;
                swapped = 1;
            }
        }
        if (!swapped) break; /* Already sorted: finish early. */
    }
}

void sortTransactions(double transactions[], int count)
{
    bubbleSortFloats(transactions, count);
}

double calculateBalance(const double transactions[], int count)
{
    if (transactions == NULL || count <= 0) return 0.0;

    double balance = 0.0;
    for (int i = 0; i < count; i++) balance += transactions[i];
    return balance;
}

void printTransactions(const double transactions[], int count)
{
    if (transactions != NULL && count > 0)
    {
        for (int i = 0; i < count; i++)
        {
            if (i > 0) printf(" ");
            printf("%.2f", transactions[i]);
        }
    }
    printf("\n");
}

/* ---- User interface helpers ---- */

void printBalance(double balance)
{
    printf("Balance: $%.2f\n", balance);
}

void printMenu(void)
{
    printf("\n1. Deposit\n");
    printf("2. Withdraw\n");
    printf("3. Show Balance\n");
    printf("4. Sorted Statement\n");
    printf("5. Save & Quit\n");
}
