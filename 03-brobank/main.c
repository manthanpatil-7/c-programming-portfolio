#include <stdio.h>
#include "bank.h"

/*
 * main.c — BroBank entry point
 *
 * Owns the menu loop, input validation, and the session history. All
 * account rules, persistence, and sorting live behind the bank.h
 * interface, so this file never manipulates the balance directly.
 */

int main(void)
{
    double balance = loadBalance();

    /* Successful transactions this session, as signed amounts:
     * deposits positive, withdrawals negative. */
    double session[MAX_TRANSACTIONS];
    int sessionCount = 0;

    double amount = 0.0;
    char choice = '\0';

    printf("=== BroBank ===\n");
    printf("Current balance: $%.2f\n", balance);

    do
    {
        printMenu();
        printf("Choice: ");
        if (scanf(" %c", &choice) != 1)
        {
            saveBalance(balance);
            return 1;
        }

        if (choice == '1' || choice == 'D' || choice == 'd')
        {
            printf("Deposit amount: $");
            if (scanf("%lf", &amount) != 1)
            {
                printf("Invalid amount\n");
                saveBalance(balance);
                return 1;
            }
            if (amount <= 0.0)
            {
                printf("Invalid amount\n");
            }
            else
            {
                deposit(&balance, amount);
                logTransaction("Deposit", amount, balance);
                if (sessionCount < MAX_TRANSACTIONS)
                {
                    session[sessionCount++] = amount;
                }
                printf("Deposit successful. ");
                printBalance(balance);
            }
        }
        else if (choice == '2' || choice == 'W' || choice == 'w')
        {
            printf("Withdrawal amount: $");
            if (scanf("%lf", &amount) != 1)
            {
                printf("Invalid amount\n");
                saveBalance(balance);
                return 1;
            }
            if (withdraw(&balance, amount))
            {
                logTransaction("Withdraw", amount, balance);
                if (sessionCount < MAX_TRANSACTIONS)
                {
                    session[sessionCount++] = -amount;
                }
                printf("Withdrawal successful. ");
                printBalance(balance);
            }
            else if (amount <= 0.0)
            {
                printf("Invalid amount\n");
            }
            else
            {
                printf("Insufficient funds. Withdrawal rejected.\n");
            }
        }
        else if (choice == '3' || choice == 'B' || choice == 'b')
        {
            printBalance(balance);
        }
        else if (choice == '4' || choice == 'S' || choice == 's')
        {
            if (sessionCount == 0)
            {
                printf("No transactions this session\n");
            }
            else
            {
                /* Sort a copy so the chronological history is preserved. */
                double sorted[MAX_TRANSACTIONS];
                for (int i = 0; i < sessionCount; i++)
                {
                    sorted[i] = session[i];
                }
                sortTransactions(sorted, sessionCount);
                printf("Sorted transactions: ");
                printTransactions(sorted, sessionCount);
                printf("Net change this session: $%.2f\n",
                       calculateBalance(sorted, sessionCount));
            }
        }
        else if (choice != '5' && choice != 'Q' && choice != 'q')
        {
            printf("Invalid choice\n");
        }
    }
    while (choice != '5' && choice != 'Q' && choice != 'q');

    saveBalance(balance);
    printf("Balance saved. Goodbye!\n");
    return 0;
}
