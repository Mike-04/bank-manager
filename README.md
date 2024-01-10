# Banking System Program Documentation

## Overview

The Banking System program is a simple command-line application that allows users to perform banking operations such as login, sign-up, deposit, withdrawal, transfer, and view transaction history.

## File Structure

- `main.c`: Contains the main logic of the program.
- `calendar.h`: Header file with functions for working with dates.
- `utils.h`: Header file with utility functions for string manipulation and input validation.

## `main.c` Functions

### `int main()`

- **Purpose**: The main function containing the program logic.
- **Return**: Returns 0 upon successful execution.

### `int validate_option(char *s, int n)`

- **Purpose**: Validates user input option against a list of valid options.
- **Parameters**:
  - `char *s` - The user input option.
  - `int n` - The number of valid options.
- **Return**: Returns 1 if the option is valid, 0 otherwise.

### `int logged_in_menu()`

- **Purpose**: Displays the logged-in menu and gets the user's choice.
- **Return**: Returns the user's choice as an integer.

### `int login_menu()`

- **Purpose**: Displays the login menu and gets the user's choice.
- **Return**: Returns the user's choice as an integer.

### `int login()`

- **Purpose**: Validates user login credentials.
- **Return**: Returns the user ID upon successful login, 0 otherwise.

### `void sign_up()`

- **Purpose**: Handles user sign-up.
- **Side Effect**: Modifies the global array `A` with user account information.

### `void log_out()`

- **Purpose**: Logs out the current user.
- **Side Effect**: Logs the logout activity in "history.txt".

### `int load_data_from_file()`

- **Purpose**: Loads data from files into the program.
- **Return**: Returns 1 upon successful data loading, 0 otherwise.

### `float user_balance(int id)`

- **Purpose**: Calculates the user's balance based on transactions.
- **Parameters**: `int id` - The user ID.
- **Return**: Returns the user's balance as a floating-point number.

### `void print_user_balance(int id)`

- **Purpose**: Prints the user's current balance.
- **Parameters**: `int id` - The user ID.

### `void save_transaction()`

- **Purpose**: Saves transactions to a file.
- **Side Effect**: Modifies the "transaction.txt" file.

### `void deposit(int id)`

- **Purpose**: Handles user deposit operation.
- **Parameters**: `int id` - The user ID.

### `void withdraw(int id)`

- **Purpose**: Handles user withdrawal operation.
- **Parameters**: `int id` - The user ID.

### `int id_existent(int x)`

- **Purpose**: Checks if a given ID exists in the user accounts.
- **Parameters**: `int x` - The ID to check.
- **Return**: Returns the index of the ID in the `A` array if it exists, 0 otherwise.

### `void transfer(int id)`

- **Purpose**: Handles user transfer operation.
- **Parameters**: `int id` - The user ID.

### `void print_all_transactions(int id)`

- **Purpose**: Prints all transactions for a user.
- **Parameters**: `int id` - The user ID.

### `void export_to_csv(int id)`

- **Purpose**: Exports all user transactions to a CSV file.
- **Parameters**: `int id` - The user ID.
- **Side Effect**: Creates or modifies "transactions.csv" file.

### `void print_account_statement(int id)`

- **Purpose**: Prints the account statement for a user within a date range.
- **Parameters**: `int id` - The user ID.

### `void print_customer_report(int id)`

- **Purpose**: Prints a report of customers with whom the user has transacted.
- **Parameters**: `int id` - The user ID.

### `void print_history(int id)`

- **Purpose**: Prints the transaction history for a user.
- **Parameters**: `int id` - The user ID.

## Usage

Compile and run the program using a C compiler. Follow the on-screen instructions to navigate through the menu and perform banking operations.

