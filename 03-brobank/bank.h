#ifndef BANK_H
#define BANK_H

/*
 * bank.h — public interface of the BroBank banking application
 *
 * main.c programs exclusively against these declarations; bank.c owns all
 * account rules, file access, and sorting. Session statements work with
 * signed amounts: deposits are positive, withdrawals negative.
 */

#define MAX_TRANSACTIONS 100

/* ---- Account operations ---- */

/* Adds amount to *balance. No-op if balance is NULL or amount <= 0. */
void deposit(double *balance, double amount);

/* Subtracts amount from *balance and returns 1 on success. Returns 0 —
 * leaving the balance unchanged — if balance is NULL, amount <= 0, or the
 * funds are insufficient. */
int withdraw(double *balance, double amount);

/* ---- Persistence and logging ---- */

/* Returns the balance stored in brobank_data.txt, or 0.00 when the file
 * is missing or unreadable (a fresh account). */
double loadBalance(void);

/* Writes the balance to brobank_data.txt for the next run. */
void saveBalance(double balance);

/* Appends one dated CSV record of a successful transaction to
 * transactions.txt. */
void logTransaction(const char type[], double amount, double balance);

/* ---- Session statement ---- */

/* Sorts n doubles ascending, in place (bubble sort with early exit). */
void bubbleSortFloats(double arr[], int n);

/* Sorts a session's signed transaction amounts in place. */
void sortTransactions(double transactions[], int count);

/* Returns the sum of the signed amounts: the session's net change. */
double calculateBalance(const double transactions[], int count);

/* Prints the amounts on one line, two decimals, space-separated. */
void printTransactions(const double transactions[], int count);

/* ---- User interface helpers ---- */

void printBalance(double balance);
void printMenu(void);

#endif
