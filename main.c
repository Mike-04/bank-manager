#include "calendar.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int is_logged = 0, next_user_id = 0;
char user_name[100];
struct Account {
  int id;
  char user[100];
  char pass[100];
  char name[100];
} A[1000];
struct Transaction {
  int id_from, id_to;
  char desc[100];
  struct date data;
  float amount;
} T[10000];

int number_account = 0, number_transaction = 0;
int validate_option(char *s, int n) {
  // Function to validate user input option
  char val_op[10][10] = {"1", "2", "3", "4", "5", "6", "7", "8", "9", "10"};
  int i;
  for (i = 0; i < n; i++)
    if (strcmp(val_op[i], s) == 0)
      return 1;
  return 0;
}

int logged_in_menu() {
  // Function to display the logged-in menu and get user's choice
  printf("\n%s\n", user_name);
  printf("1. Sold\n");
  printf("2. deposit\n");
  printf("3. Withdrawals\n");
  printf("4. Transfer\n");
  printf("5. All transaction\n");
  printf("6. Export All transaction\n");
  printf("7. Account statement\n");
  printf("8. Customer\n");
  printf("9. History\n");
  printf("10. Logout\n");
  char option[100];
  printf("Option:");
  scanf("%s", option);
  if (!validate_option(option, 10))
    return 0;
  else
    return atoi(option);
}
int login_menu() {
  // Function to display the login menu and get user's choice
  printf("1. Login\n");
  printf("2. Sign up\n");
  printf("3. Exit\n");
  char option[100];
  printf("Option:");
  scanf("%s", option);
  if (!validate_option(option, 3))
    return 0;
  else
    return atoi(option);
}
int login() {
  // Function to validate user login credentials
  char user[100], pass[100];
  int i;
  printf("User name:");
  scanf("%s", user);
  printf("Password:");
  scanf("%s", pass);
  for (i = 1; i <= number_account; i++)
    if (strcmp(user, A[i].user) == 0 && strcmp(pass, A[i].pass) == 0) {
      strcpy(user_name, A[i].name);
      FILE *f_hist = fopen("history.txt", "a");
      char timp[20];
      set_current_time(timp);
      char data[20];
      data_to_str(DC, data);
      fprintf(f_hist, "%d\n%s %s %s\n", A[i].id, data, timp, "login");
      fclose(f_hist);
      return A[i].id;
    }

  printf("Invalid user name or password\n");
  return 0;
}
void sign_up() {
  // Function to handle user sign-up
  char user[100], pass[100], name[100];
  int ok = 1;
  do {
    ok = 1;
    getchar();
    printf("Name:");
    gets(name);
    if (!letters_spaces(name)) {
      printf("Name should contain letters or spaces\n");
      ok = 0;
    }

  } while (!ok);

  do {
    ok = 1;
    printf("New user name : ");
    gets(user);
    if (!letters_numbers(user)) {
      printf("User sould containt letters or numbers\n");
      ok = 0;
    } else {
      int i;
      for (i = 1; i <= number_account; i++) {
        if (strcmp(user, A[i].user) == 0) {
          printf("User already exist\n");
          ok = 0;
          break;
        }
      }
    }

  } while (!ok);
  do {
    ok = 1;
    printf("New password:");
    gets(pass);
    if (!letters_numbers(pass)) {
      printf("Password sould contain letters or numbers\n");
      ok = 0;
    }
    char conf_pass[100];
    printf("Retype password:");
    gets(conf_pass);
    if (strcmp(pass, conf_pass) != 0) {
      printf("Password not match\n");
      ok = 0;
    }

  } while (!ok);
  next_user_id++;
  number_account++;
  A[number_account].id = next_user_id;
  strcpy(A[number_account].user, user);
  strcpy(A[number_account].pass, pass);
  strcpy(A[number_account].name, name);
  FILE *F = fopen("login.txt", "a");
  fprintf(F, "%d %s %s %s\n", next_user_id, user, pass, name);
  fclose(F);

  FILE *f_hist = fopen("history.txt", "a");
  char timp[20];
  set_current_time(timp);
  char data[20];
  data_to_str(DC, data);
  fprintf(f_hist, "%d\n%s %s %s\n", next_user_id, data, timp,
          "created account");
  fclose(f_hist);
}
void log_out() {
  // Function to log out the current user
  FILE *f_hist = fopen("history.txt", "a");
  char timp[20];
  set_current_time(timp);
  char data[20];
  data_to_str(DC, data);
  fprintf(f_hist, "%d\n%s %s %s\n", is_logged, data, timp, "logout");
  fclose(f_hist);
  is_logged = 0;
}

int load_data_from_file() {
  // Function to load data from files into the program
  FILE *f_login = fopen("login.txt", "r");
  if (f_login == NULL)
    // f_login = fopen("login.txt", "w");
    return 0;
  FILE *f_trans = fopen("transaction.txt", "r");
  if (f_trans == NULL)
    return 0;

  number_account = 0;
  while (!feof(f_login)) {
    number_account++;
    fscanf(f_login, "%d %s %s", &A[number_account].id, &A[number_account].user, &A[number_account].pass);
    fgets(A[number_account].name, 100, f_login);
    remove_null(A[number_account].name);
    remove_beginning_space(A[number_account].name);
    if (!feof(f_login))
      if (A[number_account].id > next_user_id)
        next_user_id = A[number_account].id;
  }
  number_account--;
  fclose(f_login);
  number_transaction = 0;
  while (!feof(f_trans)) {
    number_transaction++;
    fscanf(f_trans, "%d %d %f %d %d %d", &T[number_transaction].id_from, &T[number_transaction].id_to,
           &T[number_transaction].amount, &T[number_transaction].data.zi, &T[number_transaction].data.luna, &T[number_transaction].data.an);
    fgets(T[number_transaction].desc, 100, f_trans);
    remove_beginning_space(T[number_transaction].desc);
    remove_null(T[number_transaction].desc);
  }
  number_transaction--;
  fclose(f_trans);
  return 1;
}
float user_balance(int id) {
  // Function to calculate user balance based on transactions
  float s = 0;
  int i;
  for (i = 1; i <= number_transaction; i++) {
    if (T[i].id_from == id)
      s -= T[i].amount;
    if (T[i].id_to == id)
      s += T[i].amount;
  }
  return s;
}
void print_user_balance(int id) {
  // Function to print user's current balance
  float sold = user_balance(id);
  char data[20];
  data_to_str(DC, data);
  printf("%s\n", user_name);
  printf("Your sold %8.2f current date %s", sold, data);
  FILE *f_hist = fopen("history.txt", "a");
  char timp[20];
  set_current_time(timp);
  fprintf(f_hist, "%d\n%s %s %s %.2f\n", is_logged, data, timp, "list sold ",
          sold);
  fclose(f_hist);
}

void save_transaction() {
  // Function to save transactions to a file
  FILE *F = fopen("transaction.txt", "w");
  int i;
  for (i = 1; i <= number_transaction; i++)
    fprintf(F, "%d %d %.2f %d %d %d %s\n", T[i].id_from, T[i].id_to,
            T[i].amount, T[i].data.zi, T[i].data.luna, T[i].data.an, T[i].desc);
  fclose(F);
}
void deposit(int id) {
  // Function to handle user deposit operation
  float sum;
  printf("Amount deposit: ");
  char sir[20];
  scanf("%s", sir);
  sum = validate_number(sir);
  if (sum) {
    number_transaction++;
    T[number_transaction].amount = sum;
    strcpy(T[number_transaction].desc, "deposit");
    T[number_transaction].id_to = id;
    T[number_transaction].id_from = 0;
    T[number_transaction].data = DC;
    save_transaction();

    FILE *f_hist = fopen("history.txt", "a");
    char timp[20];
    set_current_time(timp);
    char data[20];
    data_to_str(DC, data);
    fprintf(f_hist, "%d\n%s %s %s %.2f\n", is_logged, data, timp, "deposit ",
            sum);
    fclose(f_hist);
  } else
    printf("Incorrect data: \n");
}
void withdraw(int id) {
  // Function to handle user withdrawal operation
  float sum;
  printf("Amount withdrawals: ");
  char sir[20];
  scanf("%s", sir);
  sum = validate_number(sir);
  if (sum) {
    if (sum <= user_balance(id)) {
      number_transaction++;
      T[number_transaction].amount = sum;
      strcpy(T[number_transaction].desc, "withdrawals");
      T[number_transaction].id_to = 0;
      T[number_transaction].id_from = id;
      T[number_transaction].data = DC;
      save_transaction();

      FILE *f_hist = fopen("history.txt", "a");
      char timp[20];
      set_current_time(timp);
      char data[20];
      data_to_str(DC, data);
      fprintf(f_hist, "%d\n%s %s %s %.2f\n", is_logged, data, timp,
              "withdrawals ", sum);
      fclose(f_hist);
    } else
      printf("Insufficient funds: \n");
  } else
    printf("Incorrect data: \n");
}
int id_existent(int x) {
  // Function to check if a given ID exists in the user accounts
  int i;
  for (i = 1; i <= number_account; i++)
    if (A[i].id == x)
      return i;
  return 0;
}
void transfer(int id) {
  // Function to handle user transfer operation
  float sum;
  int id_to_transfer;
  printf("Id to transfer ");
  scanf("%d", &id_to_transfer);
  int poz = id_existent(id_to_transfer);
  if (!poz)
    printf("Id not exist\n");
  else {
    printf("Amount to transfer : ");
    char sir[20];
    scanf("%s", sir);
    sum = validate_number(sir);
    if (sum)
      if (sum <= user_balance(id)) {
        number_transaction++;
        T[number_transaction].amount = sum;
        char desc[200] = "transfer to ";
        strcat(desc, A[poz].name);
        strcat(desc, "    from ");
        strcat(desc, user_name);

        strcpy(T[number_transaction].desc, desc);
        T[number_transaction].id_to = id_to_transfer;
        T[number_transaction].id_from = id;
        T[number_transaction].data = DC;
        save_transaction();

        FILE *f_hist = fopen("history.txt", "a");
        char timp[20];
        set_current_time(timp);
        char data[20];
        data_to_str(DC, data);
        fprintf(f_hist, "%d\n%s %s %s %s %.2f   lei\n", is_logged, data, timp,
                "transfer to  ", A[poz].name, sum);
        fclose(f_hist);
      } else
        printf("Insufficient funds: \n");
    else
      printf("Incorrect data: \n");
  }
}
void print_all_transactions(int id) {
  // Function to print all transactions for a user
  int i;
  for (i = 1; i <= number_transaction; i++)
    if (T[i].id_from == id)
      printf("%10.2f lei  %2d-%2d-%4d %60s\n", -T[i].amount, T[i].data.zi,
             T[i].data.luna, T[i].data.an, T[i].desc);
    else if (T[i].id_to == id)
      printf("%10.2f lei  %2d-%2d-%4d %60s\n", T[i].amount, T[i].data.zi,
             T[i].data.luna, T[i].data.an, T[i].desc);

  FILE *f_hist = fopen("history.txt", "a");
  char timp[20];
  set_current_time(timp);
  char data[20];
  data_to_str(DC, data);
  fprintf(f_hist, "%d\n%s %s %s\n", is_logged, data, timp,
          "All transaction report ");
  fclose(f_hist);
}

void export_to_csv(int id) {
    FILE *csvFile = fopen("transactions.csv", "w");

    if (csvFile) {
        fprintf(csvFile, "ID_From,ID_To,Amount,Date,Description\n");

        for (int i = 1; i <= number_transaction; i++) {
            if (T[i].id_from == id || T[i].id_to == id) {
                char data[20] = "";
                data_to_str(T[i].data, data);

                fprintf(csvFile, "%d,%d,%.2f,%s,%s\n", T[i].id_from, T[i].id_to, T[i].amount, data, T[i].desc);
            }
        }

        fclose(csvFile);

        FILE *f_hist = fopen("history.txt", "a");
        char timp[20]; 
        set_current_time(timp); 
        char data[20]; 
        data_to_str(DC, data);
        fprintf(f_hist, "%d\n%s %s %s\n", id, data, timp, "export all transactions to CSV");
        fclose(f_hist);
    } else {
        printf("Error opening CSV file for writing\n");
    }
}

void print_account_statement(int id) {
  // Function to print account statement for a user within a date range
  struct date d1, d2;
  printf("Input starting date: \n");
  int date_valide = 1;
  do {
    date_valide = 1;
    printf("Day:");
    scanf("%d", &d1.zi);
    printf("Month:");
    scanf("%d", &d1.luna);
    printf("Year:");
    scanf("%d", &d1.an);
    if (!validate_date(d1)) {
      printf("Invalid date!\n");
      date_valide = 0;
    }
  } while (date_valide == 0);
  printf("Input final date: \n");
  date_valide = 1;
  do {
    date_valide = 1;
    printf("Day:");
    scanf("%d", &d2.zi);
    printf("Month:");
    scanf("%d", &d2.luna);
    printf("Year:");
    scanf("%d", &d2.an);
    if (!validate_date(d2)) {
      printf("Invalid date!\n");
      date_valide = 0;
    }
    if (cmp_date(d1, d2) > 0) {
      printf("Final date must be after starting date\n");
      date_valide = 0;
    }
  } while (date_valide == 0);
  int i = 0;
  float s_input = 0, s_output = 0;
  for (i = 1; i <= number_transaction; i++) {
    if (cmp_date(T[i].data, d1) >= 0 && cmp_date(T[i].data, d2) <= 0) {
      char str_data[20];
      data_to_str(T[i].data, str_data);
      if (T[i].id_from == id) {
        printf("%10s lei %8.2f  %s\n", str_data, -T[i].amount, T[i].desc);
        s_output += T[i].amount;
      }
      if (T[i].id_to == id) {
        printf("%10s lei %8.2f  %s\n", str_data, T[i].amount, T[i].desc);
        s_input += T[i].amount;
      }
    }
  }
  printf(" Total entries : %.2f \n", s_input);
  printf(" Total outputs : %.2f \n", s_output);

  FILE *f_hist = fopen("history.txt", "a");
  char timp[20];
  set_current_time(timp);
  char data[20];
  data_to_str(DC, data);
  fprintf(f_hist, "%d\n%s %s %s\n", is_logged, data, timp,
          "Account statement ");
  fclose(f_hist);
}
void print_customer_report(int id) {
  // Function to print a report of customers with whom the user has transacted
  printf("Customers: \n");
  int C[10000] = {}, i, j;
  for (i = 1; i <= number_transaction; i++) {
    if (T[i].id_from == id && T[i].id_to != 0)
      C[T[i].id_to] = 1;
    if (T[i].id_to == id && T[i].id_from != 0)
      C[T[i].id_from] = 1;
  }
  for (i = 1; i <= 9999; i++)
    if (C[i] != 0)
      for (j = 1; j <= number_account; j++)
        if (A[j].id == i)
          printf("%s\n", A[i].name);

  FILE *f_hist = fopen("history.txt", "a");
  char timp[20];
  set_current_time(timp);
  char data[20];
  data_to_str(DC, data);
  fprintf(f_hist, "%d\n%s %s %s \n", is_logged, data, timp, "Customer report ");
  fclose(f_hist);
}
void print_history(int id) {
  // Function to print transaction history for a user
  FILE *f_hist = fopen("history.txt", "r");
  int idh;
  char text[200] = "";
  fgetc(f_hist);
  while (!feof(f_hist)) {

    fscanf(f_hist, "%d", &idh);
    fgetc(f_hist);
    fgets(text, 200, f_hist);
    if (!feof(f_hist))
      if (id == idh)
        printf(text);
  }
}
int main() {
  // Main function containing the program logic
  set_current_date();
  if (load_data_from_file())
    while (1) {
      if (is_logged) {
        int option = logged_in_menu();
        if (option == 0)
          printf("Not a valid option\n");
        else if (option == 1)
          print_user_balance(is_logged);
        else if (option == 2)
          deposit(is_logged);
        else if (option == 3)
          withdraw(is_logged);
        else if (option == 4)
          transfer(is_logged);
        else if (option == 5)
          print_all_transactions(is_logged);
        else if (option == 6)
          export_to_csv(is_logged);
        else if (option == 7)
          print_account_statement(is_logged);
        else if (option == 8)
          print_customer_report(is_logged);
        else if (option == 9)
          print_history(is_logged);
        else if (option == 10)
          log_out();
      } else {
        int option = login_menu();
        if (option == 0)
          printf("Not a valid option\n");
        else if (option == 1)
          is_logged = login();
        else if (option == 2)
          sign_up();
        else if (option == 3)
          break;
      }
    }
  else
    printf("File error!");
  return 0;
}