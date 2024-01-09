#include <stdio.h>
#include <stdlib.h>
# include <string.h>
# include "utils.h"
# include "calendar.h"
// #include "xlsxwriter.h"

int is_logged = 0, next_user_id=0; char user_name[100];
struct Account
{
    int id;
    char user[100];
    char pass[100];
    char name[100];
}A[1000];
struct Transaction
{
    int id_from, id_to;
    char desc[100];
    struct date data;
    float amount;
}T[10000];
int N_A=0, N_T=0;
int valid_option(char *s, int n)
{
    char val_op[10][10]={"1", "2", "3", "4", "5", "6", "7", "8", "9", "10"};
    int i;
    for (i = 0; i<n; i++)
        if(strcmp(val_op[i], s) == 0)
            return 1;
    return 0;
}
int Logged_menu()
{
    printf("\n%s\n", user_name);
    printf("%s\n", "------------------------------------");;
    printf("1. Sold\n");
    printf("2. Deposit\n");
    printf("3. Withdrawals\n");
    printf("4. Transfer\n");
    printf("5. All transaction\n");
    printf("6. Export All transaction\n");
    printf("7. Account statement\n");
    printf("8. Customer\n");
    printf("9. History\n");
    printf("10. Logout\n");
    char option[100];
    printf("option: ");scanf("%s", option);
    if (! valid_option(option, 10))
        return 0;
    else
        return atoi(option);
}
int Login_menu()
{
    printf("1. Login\n");
    printf("2. Sign up\n");
    printf("3. Exit\n");
    char option[100];
    printf("option: ");scanf("%s", option);
    if (! valid_option(option, 3))
        return 0;
    else
        return atoi(option);
}
int Login()
{
    char user[100], pass[100]; int i;
    printf("user name : "); scanf("%s", user);
    printf("password  : "); scanf("%s", pass);
    for (i = 1; i<=N_A ; i++)
        if(strcmp(user, A[i].user) == 0 && strcmp(pass, A[i].pass) == 0)
        {
            strcpy(user_name, A[i].name);
            FILE * f_hist = fopen("history.txt", "a");
            char timp[20]; Time(timp); char data[20]; data_to_str(DC, data);
            fprintf(f_hist, "%d\n%s %s %s\n", A[i].id, data, timp, "login");
            fclose(f_hist);
            return A[i].id;
        }

    printf("Invalid user name or password\n");
    return 0;
}
void Sign_up()
{
    char user[100], pass[100], name[100]; int ok = 1;
    do
    {
        ok = 1;
        getchar();
        printf("name          : "); gets(name);
        if(! isalpha_or_space(name))
        {
            printf("name should be alfa or space\n");
            ok = 0;
        }

    }while(!ok);

    do
    {
        ok = 1;
        printf("new user name : "); gets(user);
        if(! isalpha_or_number(user))
        {
            printf("user sould be alfa or number\n");
            ok = 0;
        }
        else
        {
            int i;
            for (i = 1; i<=N_A; i++)
            {
                if(strcmp(user, A[i].user) == 0)
                {
                    printf("user already exist\n");
                    ok = 0;
                    break;
                }
            }
        }

    }while(!ok);
    do
    {
        ok = 1;
        printf("new password  : "); gets(pass);
        if(! isalpha_or_number(pass))
        {
            printf("password sould be alfa or number\n");
            ok = 0;
        }
        char conf_pass[100];
        printf("retype password  : "); gets(conf_pass);
        if (strcmp(pass, conf_pass) != 0)
        {
            printf("password not match\n");
            ok = 0;
        }

    }while(!ok);
    next_user_id++;
    N_A++; A[N_A].id=next_user_id; strcpy(A[N_A].user,user); strcpy(A[N_A].pass,pass); strcpy(A[N_A].name,name);
    FILE * F = fopen("login.txt", "a");
    fprintf(F, "%d %s %s %s\n", next_user_id, user, pass, name);
    fclose(F);

    FILE * f_hist = fopen("history.txt", "a");
    char timp[20]; Time(timp); char data[20]; data_to_str(DC, data);
    fprintf(f_hist, "%d\n%s %s %s\n", next_user_id, data, timp, "created account");
    fclose(f_hist);
}
void Logout()
{
    FILE * f_hist = fopen("history.txt", "a");
    char timp[20]; Time(timp); char data[20]; data_to_str(DC, data);
    fprintf(f_hist, "%d\n%s %s %s\n", is_logged, data, timp, "logout");
    fclose(f_hist);
    is_logged = 0;
}
int load_data_base_from_file()
{
    FILE * f_login = fopen("login.txt", "r");
    if (f_login == NULL)
        //f_login = fopen("login.txt", "w");
        return 0;
    FILE * f_trans = fopen("transaction.txt", "r");
    if (f_trans == NULL)
        return 0;

    N_A = 0;
    while (!feof(f_login))
    {
        N_A++;
        fscanf(f_login, "%d %s %s", &A[N_A].id, &A[N_A].user, &A[N_A].pass);
        fgets(A[N_A].name, 100, f_login); Elimina_bn(A[N_A].name); Elimina_spatiu_inceput(A[N_A].name);
        if(!feof(f_login))
            if(A[N_A].id > next_user_id)
                next_user_id = A[N_A].id;
    }
    N_A--;
    fclose(f_login);
    N_T = 0;
    while (!feof(f_trans))
    {
        N_T++;
        fscanf(f_trans, "%d %d %f %d %d %d", &T[N_T].id_from, &T[N_T].id_to, &T[N_T].amount, &T[N_T].data.zi, &T[N_T].data.luna, &T[N_T].data.an);
        fgets(T[N_T].desc , 100, f_trans); Elimina_spatiu_inceput(T[N_T].desc);Elimina_bn(T[N_T].desc);

    }
    N_T--;
    fclose(f_trans);
    /*
    int i;
    for (i = 1; i<=N_T; i++)
        printf("%d %d %.2f %d-%d-%d %s\n", T[i].id_from, T[i].id_to, T[i].amount, T[i].data.zi, T[i].data.luna, T[i].data.an, T[i].desc);*/
    return 1;
}
float Sold_user (int id)
{
    float s = 0; int i;
    for (i = 1; i<=N_T ; i++)
    {
        if(T[i].id_from == id)
            s -= T[i].amount;
        if(T[i].id_to == id)
            s += T[i].amount;
    }
    return s;
}
void List_Sold_User(int id)
{
    float sold = Sold_user(id);
    printf("\n--------------------------------------------\n");
    char data[20];
    data_to_str(DC, data);
    printf("%s\n",user_name);
    printf("Your sold %8.2f     current date %s", sold, data);
    printf("\n--------------------------------------------\n");
    FILE * f_hist = fopen("history.txt", "a");
    char timp[20]; Time(timp);
    fprintf(f_hist, "%d\n%s %s %s %.2f\n", is_logged, data, timp, "list sold ", sold);
    fclose(f_hist);
}
void Save_Transaction()
{
    FILE* F=fopen("transaction.txt", "w");
    int i;
    for (i=1; i<=N_T; i++)
        fprintf(F, "%d %d %.2f %d %d %d %s\n", T[i].id_from, T[i].id_to, T[i].amount, T[i].data.zi, T[i].data.luna, T[i].data.an, T[i].desc);
    fclose(F);
}
void Deposit (int id)
{
    printf("\n--------------------------------------------\n");
    float sum;
    printf("Amount deposit: "); char sir[20]; scanf("%s", sir);
    sum = Valid_number(sir);
    if(sum)
    {
        N_T++;
        T[N_T].amount=sum;
        strcpy(T[N_T].desc, "deposit");
        T[N_T].id_to = id;
        T[N_T].id_from = 0;
        T[N_T].data = DC;
        Save_Transaction();

        FILE * f_hist = fopen("history.txt", "a");
        char timp[20]; Time(timp); char data[20]; data_to_str(DC, data);
        fprintf(f_hist, "%d\n%s %s %s %.2f\n", is_logged, data, timp, "deposit ", sum);
        fclose(f_hist);

    }
    else
        printf("incorrect data: \n");
    printf("\n--------------------------------------------\n");
}
void Withdrawals (int id)
{
    printf("\n--------------------------------------------\n");
    float sum;
    printf("Amount withdrawals: ");
    char sir[20]; scanf("%s", sir);
    sum = Valid_number(sir);
    if(sum)
    {
        if(sum<= Sold_user(id))
        {
            N_T++;
            T[N_T].amount=sum;
            strcpy(T[N_T].desc, "withdrawals");
            T[N_T].id_to = 0;
            T[N_T].id_from = id;
            T[N_T].data = DC;
            Save_Transaction();

            FILE * f_hist = fopen("history.txt", "a");
            char timp[20]; Time(timp); char data[20]; data_to_str(DC, data);
            fprintf(f_hist, "%d\n%s %s %s %.2f\n", is_logged, data, timp, "withdrawals ", sum);
            fclose(f_hist);
        }
        else
            printf("insufficient funds: \n");
    }
    else
        printf("incorrect data: \n");
    printf("\n--------------------------------------------\n");
}
int Exist_id(int x)
{
    int i;
    for (i = 1; i<=N_A; i++)
        if (A[i].id == x)
            return i;
    return 0;
}
void Transfer (int id)
{
    printf("\n--------------------------------------------\n");
    float sum; int id_to_transfer;
    printf("id to transfer "); scanf("%d", &id_to_transfer);
    int poz =  Exist_id(id_to_transfer);
    if(!poz)
        printf("id not exist\n");
    else
    {
        printf("Amount to transfer : ");
        char sir[20]; scanf("%s", sir);
        sum = Valid_number(sir);
        if(sum)
            if(sum<= Sold_user(id))
            {
                N_T++;
                T[N_T].amount=sum;
                char desc[200] = "transfer to ";
                strcat (desc, A[poz].name);
                strcat (desc, "    from ");
                strcat (desc, user_name);

                strcpy(T[N_T].desc, desc);
                T[N_T].id_to = id_to_transfer;
                T[N_T].id_from = id;
                T[N_T].data = DC;
                Save_Transaction();

                FILE * f_hist = fopen("history.txt", "a");
                char timp[20]; Time(timp); char data[20]; data_to_str(DC, data);
                fprintf(f_hist, "%d\n%s %s %s %s %.2f   lei\n", is_logged, data, timp, "transfer to  ",A[poz].name,  sum);
                fclose(f_hist);
            }
            else
                printf("insufficient funds: \n");
        else
        printf("incorrect data: \n");
    }
    printf("\n--------------------------------------------\n");
}
void All_Transaction(int id)
{
    printf("\n--------------------------------------------\n");
    int i;
    for (i=1; i<= N_T; i++)
        if (T[i].id_from == id)
            printf("%10.2f lei  %2d-%2d-%4d %60s\n", -T[i].amount, T[i].data.zi, T[i].data.luna,  T[i].data.an, T[i].desc);
        else
            if (T[i].id_to == id)
            printf("%10.2f lei  %2d-%2d-%4d %60s\n", T[i].amount, T[i].data.zi, T[i].data.luna,  T[i].data.an, T[i].desc);
    printf("\n--------------------------------------------\n");
    FILE * f_hist = fopen("history.txt", "a");
    char timp[20]; Time(timp); char data[20]; data_to_str(DC, data);
    fprintf(f_hist, "%d\n%s %s %s\n", is_logged, data, timp, "All transaction report ");
    fclose(f_hist);
}
void Export_All_Transaction(int id)
{
    // lxw_workbook *workbook = workbook_new("transaction.xlsx");
    // lxw_worksheet *worksheet = workbook_add_worksheet(workbook, "Sheet1");

    // if (worksheet) {
    //     lxw_format *bold_format = workbook_add_format(workbook);
    //     format_set_bold(bold_format);

    //     int linie = 1;
    //     worksheet_write_string(worksheet, linie, 1, "User Name", bold_format);

    //     float input = 0, output = 0;
    //     for (int i = 1; i <= N_T; i++) 
    //     {
    //         if (T[i].id_from == id) 
    //         {
    //             linie++;
    //             char data[20] = "";
    //             data_to_str(T[i].data, data);
    //             worksheet_write_number(worksheet, linie, 1, -T[i].amount, NULL);
    //             worksheet_write_string(worksheet, linie, 2, data, NULL);
    //             worksheet_write_string(worksheet, linie, 5, T[i].desc, NULL);
    //             output += T[i].amount;
    //         }

    //         if (T[i].id_to == id) 
    //         {
    //             linie++;
    //             char data[20] = "";
    //             data_to_str(T[i].data, data);
    //             worksheet_write_number(worksheet, linie, 1, T[i].amount, NULL);
    //             worksheet_write_string(worksheet, linie, 2, data, NULL);
    //             worksheet_write_string(worksheet, linie, 5, T[i].desc, NULL);
    //             input += T[i].amount;
    //         }
    //     }

    //     linie += 3;
    //     worksheet_write_string(worksheet, linie, 1, "Total input", bold_format);
    //     worksheet_write_number(worksheet, linie, 2, input, NULL);

    //     linie += 2;
    //     worksheet_write_string(worksheet, linie, 1, "Total output", bold_format);
    //     worksheet_write_number(worksheet, linie, 2, output, NULL);

    //     linie += 2;
    //     worksheet_write_string(worksheet, linie, 1, "SOLD: ", bold_format);
    //     worksheet_write_number(worksheet, linie, 2, input - output, NULL);

    //     workbook_close(workbook);

    //     FILE *f_hist = fopen("history.txt", "a");
    //     char timp[20];
    //     Time(timp);
    //     char data[20];
    //     data_to_str(DC, data);
    //     fprintf(f_hist, "%d\n%s %s %s\n", is_logged, data, timp, "export all transactions to Excel");
    //     fclose(f_hist);
    // }
}

void Account_Statement(int id)
{
    printf("\n--------------------------------------------\n");
    struct date d1, d2;
    printf ("Input start date: \n");
    int  date_valide = 1;
    do
    {
        date_valide = 1;
        printf ("           Day  : "); scanf("%d", &d1.zi);
        printf ("           Month: "); scanf("%d", &d1.luna);
        printf ("           Year : "); scanf("%d", &d1.an);
        if (!Format_Valid_Data(d1))
        {
                printf ("  !! incorrect start date     : \n");
                date_valide = 0;
        }
    }while (date_valide==0);
    printf ("Input final date: \n");
    date_valide = 1;
    do
    {
        date_valide = 1;
        printf ("           Day  : "); scanf("%d", &d2.zi);
        printf ("           Month: "); scanf("%d", &d2.luna);
        printf ("           Year : "); scanf("%d", &d2.an);
        if (!Format_Valid_Data(d2))
        {
                printf ("  !! incorrect final date     : \n");
                date_valide = 0;
        }
        if (Compara_Data(d1, d2)>0)
        {
                printf ("  !! final date must be after start date     : \n");
                date_valide = 0;
        }
    }while (date_valide==0);
    int i = 0; float s_input = 0, s_output = 0;
    for (i = 1; i<=N_T; i++)
    {
        if (Compara_Data(T[i].data, d1)>=0 && Compara_Data(T[i].data, d2)<=0)
        {
            char str_data[20];
            data_to_str(T[i].data, str_data);
            if(T[i].id_from == id)
            {
                printf("%10s lei %8.2f  %s\n", str_data, -T[i].amount, T[i].desc);
                s_output += T[i].amount;
            }
            if(T[i].id_to == id)
            {
                printf("%10s lei %8.2f  %s\n", str_data, T[i].amount, T[i].desc);
                s_input += T[i].amount;
            }
        }
    }
    printf ("\n----------------------------\n Total entries : %.2f \n", s_input);
    printf ("\n----------------------------\n Total outputs : %.2f \n", s_output);
    printf("\n--------------------------------------------\n");

    FILE * f_hist = fopen("history.txt", "a");
    char timp[20]; Time(timp); char data[20]; data_to_str(DC, data);
    fprintf(f_hist, "%d\n%s %s %s\n", is_logged, data, timp, "account statement ");
    fclose(f_hist);

}
void Customer (int id)
{
    printf("\n--------------------------------------------\n");
    printf("Customers: \n");
    int C[10000]={}, i, j;
    for (i = 1; i<=N_T; i++)
    {
        if (T[i].id_from == id && T[i].id_to !=0)
            C[T[i].id_to] = 1;
        if (T[i].id_to == id && T[i].id_from !=0)
            C[T[i].id_from] = 1;
    }
    for (i = 1; i<=9999; i++)
        if (C[i]!=0)
            for (j=1; j<=N_A; j++)
                if (A[j].id == i)
                    printf("%s\n", A[i].name);
    printf("\n--------------------------------------------\n");
    FILE * f_hist = fopen("history.txt", "a");
    char timp[20]; Time(timp); char data[20]; data_to_str(DC, data);
    fprintf(f_hist, "%d\n%s %s %s \n", is_logged, data, timp, "Customer report ");
    fclose(f_hist);
}
void History(int id)
{
    printf("\n--------------------------------------------\n");
    FILE * f_hist = fopen("history.txt", "r");
    int idh; char text[200]="";
    fgetc(f_hist);
    while (!feof(f_hist))
    {

        fscanf(f_hist, "%d", &idh);fgetc(f_hist);
        fgets(text, 200, f_hist);
        if(! feof(f_hist))
            if (id == idh)
                printf(text);
    }
    printf("\n--------------------------------------------\n");
}
int main()
{

    Set_Data();
    if(load_data_base_from_file())
        while(1)
        {
            if (is_logged)
            {
                int option = Logged_menu();
                if(option ==0 ) printf("Not a valid option\n");
                else if(option == 1)  List_Sold_User(is_logged);
                else if(option == 2)  Deposit(is_logged);
                else if(option == 3)  Withdrawals(is_logged);
                else if(option == 4)  Transfer(is_logged);
                else if(option == 5)  All_Transaction(is_logged);
                else if(option == 6)  Export_All_Transaction(is_logged);
                else if(option == 7)  Account_Statement(is_logged);
                else if(option == 8)  Customer(is_logged);
                else if(option == 9)  History(is_logged);
                else if(option == 10) Logout();

            }
            else
            {
                int option = Login_menu();
                if(option ==0 ) printf("Not a valid option\n");
                else if(option == 1) is_logged = Login();
                else if(option == 2) Sign_up();
                else if(option == 3) break;
            }
        }
    else
        printf("the database is crashed !!");
    return 0;





}

