int isalpha_or_space(char * s)
{
    int i ;
    for (i = 0; s[i]; i++)
        if (!((s[i]>='a' && s[i]<='z') || (s[i]>='A' && s[i]<='Z') || s[i] == ' ' ))
        return 0;
    return 1;
}
int isalpha_or_number(char * s)
{
    int i ;
    for (i = 0; s[i]; i++)
        if (!((s[i]>='a' && s[i]<='z') || (s[i]>='A' && s[i]<='Z') || (s[i] >= '0' && s[i]<='9' ) ) )
        return 0;
    return 1;
}
void Elimina_bn(char * s) /// o functie ajutatoare pentru fgets (scoate ENTERUL de la sfarsitul sirului)
{
    s[strlen(s)-1]='\0';
}
void Elimina_spatiu_inceput(char * s)
{
    while(s[0] == ' ')
        strcpy(s, s+1);
}
float Valid_number(char *s)
{
    int i;
    int nr_p=0;
    for (i=0; s[i]; i++)
        if (s[i] == '.')
            nr_p++;
    if (nr_p>1)
        return 0;
    for (i=0; s[i]; i++)
        if (!( s[i]>='0' && s[i]<='9'  || s[i] =='.'))
            return 0;
    return atof(s);
}
