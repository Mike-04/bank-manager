# include <time.h>

typedef struct date
{
    int luna, zi, an;
};
struct date DC;

int eAnBisect(int numar)
{
    if((numar % 4 == 0) && (numar % 100 != 0))
        return 1;
    if(numar % 400 == 0)
        return 1;
    return 0;
}
int Format_Valid_Data(struct date d)
{
    if(d.luna > 12 || d.luna<1) return 0;
    if (d.luna == 1 || d.luna == 3 || d.luna == 5 || d.luna==7 || d.luna==8 || d.luna == 10 || d.luna==12)
        return (d.zi>0 && d.zi<=31);
    if (d.luna==2)
        if (eAnBisect(d.an))
            return (d.zi>0 && d.zi<=29);
        else
            return (d.zi>0 && d.zi<=28);
    if (d.luna == 4 || d.luna == 6 || d.luna == 9 || d.luna==11)
        return (d.zi>0 && d.zi<=30);
}

int Compara_Data(struct date a, struct date b)
{
    if (a.an<b.an) return -1;
    if (a.an>b.an) return 1;
    if (a.luna<b.luna) return -1;
    if (a.luna>b.luna) return 1;
    if (a.zi<b.zi) return -1;
    if (a.zi>b.zi) return 1;
    return 0;
}
/// Seteaza DATA CURENTA in variabila globala DC
void Set_Data()
{
    time_t s;
    struct tm* current_time;
    s = time(NULL);
    current_time = localtime(&s);

    DC.zi = current_time->tm_mday;
    DC.luna = current_time->tm_mon + 1;
    DC.an = current_time->tm_year + 1900;

}
void Time(char * rez)
{
    time_t s;
    struct tm* current_time;
    s = time(NULL);
    current_time = localtime(&s);

    char time_sir[20]="";
    char sir[10];
    itoa(current_time->tm_hour, sir, 10);
    strcat(time_sir, sir); strcat(time_sir, ":");
    itoa(current_time->tm_min, sir, 10);
    strcat(time_sir, sir); strcat(time_sir, ":");
    itoa(current_time->tm_sec, sir, 10);
    strcat(time_sir, sir);
    strcpy(rez, time_sir);
}
void data_to_str(struct date d, char* s)
{
    int zi =d.zi, luna= d.luna, an=d.an;
    s[0]='\0';
    char str_zi[5], str_luna[5], str_an[5];
    itoa(zi, str_zi, 10);
    itoa(luna, str_luna, 10);
    itoa(an, str_an, 10);
    strcat (s, str_zi);
    strcat (s, "-");
    strcat (s, str_luna);
    strcat (s, "-");
    strcat (s, str_an);
}
