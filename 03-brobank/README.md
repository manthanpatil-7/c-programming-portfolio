# BroBank

## Overview

BroBank is a command-line banking application built incrementally across the
course. It keeps a persistent account balance between runs, validates every
transaction (rejecting invalid amounts and overdrafts), writes a dated log of
each successful transaction, and can print a sorted statement of the current
session. The final program is organized as three files behind a single
public interface.

## Key Features

- **Persistent balance** — loaded from `brobank_data.txt` on startup and
  saved on quit; a missing file simply starts a new account at $0.00
- **Transaction log** — every successful deposit and withdrawal is appended
  to `transactions.txt` as a dated CSV line; rejected transactions are never
  logged
- **Validation rules** — non-numeric input, non-positive amounts, and
  overdrafts are all rejected with clear messages and the balance unchanged
- **Sorted session statement** — a menu option sorts the session's signed
  transactions (bubble sort) and reports the net change
- **Forgiving menu** — accepts both numbers (`1`–`5`) and letters
  (`D`/`W`/`B`/`S`/`Q`), upper- or lowercase

## Technical Highlights

Modular C with a header interface (`bank.h`), pointer-based account
operations, text-file persistence with defensive `fopen`/`fclose` handling,
sorting reuse through a small internal API, and input validation on every
`scanf`.

## Project Structure

| File | Responsibility |
| --- | --- |
| `main.c` | Menu loop, user input, and the session transaction history |
| `bank.c` | Account rules, file persistence, logging, sorting, and display helpers |
| `bank.h` | The public interface `main.c` programs against |
| `sample_input.txt` | Input for the demonstration session below (raw keystrokes only) |
| `sample_output.txt` | Captured output of that session on a fresh account |

## Compile and Run

```bash
gcc -std=c11 -Wall -Wextra main.c bank.c -o brobank
./brobank
```

The program creates `brobank_data.txt` and `transactions.txt` in the working
directory as it runs. To replay the demonstration session:

```bash
./brobank < sample_input.txt
```

## Example

From a fresh account, the sample session deposits $250, withdraws $75.50,
attempts a $5,000 overdraft (rejected), deposits $40.25, then prints the
sorted statement:

```text
Choice: Sorted transactions: -75.50 40.25 250.00
Net change this session: $214.75
```

Running the program a second time confirms persistence — it starts with
`Current balance: $214.75`. The full transcript is in `sample_output.txt`,
and the log after the session reads:

```text
Aug  8 2026,Deposit,250.00,250.00
Aug  8 2026,Withdraw,75.50,174.50
Aug  8 2026,Deposit,40.25,214.75
```

## Design and Testing

The central design decision is that `main()` never touches the account
directly: it reads input and calls the `bank.h` interface, so validation,
persistence, and sorting each live in one place. The most meaningful test is
the overdraft path — a withdrawal larger than the balance must leave the
balance unchanged, print a clear rejection, and write nothing to the
transaction log — which the sample session exercises alongside persistence
across two consecutive runs.

This build reorganizes the versions written for the course exercises:
the multi-file structure (Exercise 5), file persistence and logging
(Exercise 6), pointer-based account operations (Exercise 7), and the sorting
API (Exercise 8).

## Acknowledgments

This build reorganizes code I wrote for the course exercises into a single
program. Consistent with the course's AI policy, Claude (Anthropic) provided
limited assistance with logic checks and with organizing this final build.