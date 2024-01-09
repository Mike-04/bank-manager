#include <string.h>
#include <stdlib.h>
int isalpha_or_space(char *s) {
  // Function to check if a string consists of alphabetic characters or spaces
  // Returns 1 if the string is composed of alphabetic characters or spaces, 0
  // otherwise
  int i;
  for (i = 0; s[i]; i++)
    if (!((s[i] >= 'a' && s[i] <= 'z') || (s[i] >= 'A' && s[i] <= 'Z') ||
          s[i] == ' '))
      return 0;
  return 1;
}
int isalpha_or_number(char *s) {
  // Function to check if a string consists of alphabetic characters or numbers
  // Returns 1 if the string is composed of alphabetic characters or numbers, 0
  // otherwise
  int i;
  for (i = 0; s[i]; i++)
    if (!((s[i] >= 'a' && s[i] <= 'z') || (s[i] >= 'A' && s[i] <= 'Z') ||
          (s[i] >= '0' && s[i] <= '9')))
      return 0;
  return 1;
}
void remove_null(char *s) {
  // Helper function to remove the trailing newline character ('\n') from a
  // string
  s[strlen(s) - 1] = '\0';
}
void remove_beginning_space(char *s) {
  // Helper function to remove leading spaces from a string
  while (s[0] == ' ')
    strcpy(s, s + 1);
}
float validate_number(char *s) {
  // Function to validate if a string represents a valid floating-point number
  // Returns the converted floating-point number if valid, 0 otherwise
  int i;
  int nr_p = 0;
  for (i = 0; s[i]; i++)
    if (s[i] == '.')
      nr_p++;
  if (nr_p > 1)
    return 0;
  for (i = 0; s[i]; i++)
    if (!(s[i] >= '0' && s[i] <= '9' || s[i] == '.'))
      return 0;
  return atof(s);
}
