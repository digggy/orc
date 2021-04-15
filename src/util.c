#include "util.h"
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include "http.h"
#include "vector.h"

/**
 * @brief split a string into two parts at delimiter
 * @param split the string to be split
 * @param first the first part of the string
 * @param second the second part of the string
 * @param split_char the delimiter character
 * @return 0 if success else 1
 */
int split_pair_by_char(char *split, char **first, char **second,
                       char split_char) {
  char *delimiter = NULL;
  size_t delimiter_index;
  delimiter = strchr(split, split_char);
  if (!delimiter) {
    // No : found in top
    return 1;
  }
  delimiter_index = (size_t)(delimiter - split);
  *first = strn_dup(split, delimiter_index);
  *second = str_dup(split + delimiter_index + 1);
  if (!*first || !*second) {
    return 1;
  }
  return 0;
}

/**
 * Duplicates a string
 * @param c the string to be duplicated
 * @return the duplicated string
 */
char *str_dup(const char *c) {
  char *dup = malloc(strlen(c) + 1);

  if (dup != NULL) strcpy(dup, c);

  return dup;
}

/**
 * @brief duplicates a string up to size
 * Taken from original strndup source
 * @param s the string to be duplicated
 * @param n the size of the new string
 * @return the duplicated string
 */
char *strn_dup(const char *s, size_t n) {
  size_t len = strnlen(s, n);
  char *new = (char *)malloc(len + 1);
  if (new == NULL) {
    return NULL;
  }
  new[len] = '\0';
  return (char *)memcpy(new, s, len);
}

/**
 * @brief checks if string is in vector
 * @param vec the vector to be checked
 * @param value the string value
 * @return 1 if found else 0
 */
int is_in_vector(char **vec, char *value) {
  for (size_t i = 0; i < vector_size(vec); i++) {
    char *item = vec[i];
    if (strcmp(item, value) == 0) {
      return 1;
    }
  }
  return 0;
}

/**
 * @brief concatinates two string
 * @param string_one the first string
 * @param string_two the second string
 * @return the concatinated string
 */

char *concat(const char *string_one, const char *string_two) {
  // +1 for the null-terminator
//  printf("string one %s \n", string_one);
//  printf("string two %s \n", string_two);
  char *result = malloc(strlen(string_one) + strlen(string_two) + 1);
  if (result == NULL) {
    fprintf(stderr, "Memory allocation failed");
    exit(-1);
  }
  strcpy(result, string_one);
  strcat(result, string_two);
  return result;
}

/** appendstr (Append String). Appends the string 'append' to the string 'string'.
 * @param string The string in which append the new text.
 * @param append The new string to append.
 * @return returns a new string with the appended text.
 */
char * appendstr(char * string, const char * append) {
    char * newString = malloc(strlen(string) + strlen(append) + 1);

    sprintf(newString, "%s%s", string, append);
    free(string);
    return newString;
}

/**
 * strtokk (String Tokenizer). Breaks string 'string' into a series of tokens using 'strf' as a WHOLE DELIMITER string.
 * It works in the same way as strtok, so the 'string' passed as parameter is split in the different parts, breaking the 'string'.
 * @param string The contents of this string are modified and broken into smaller strings (tokens).
 * @param strf This is the C string containing the DELIMITER.
 * @return Returns a pointer to the first token found in the string. A null pointer is returned if there are no tokens left to retrieve.
 */
char * strtokk(char * string, const char * strf) {
    static char * ptr;
    static char * ptr2;

    if (!*strf) return string;
    if (string) ptr = string;
    else {
        if (!ptr2) return ptr2;
        ptr = ptr2 + strlen(strf);
    }

    if (ptr) {
        ptr2 = strstr(ptr, strf);
        if (ptr2) memset(ptr2, 0, strlen(strf));
    }
    return ptr;
}

/**
 * strrep (String Replace). Replaces 'strf' with 'strr' in 'cadena' and returns the new string.
 * You need to free the returned string in your code after using strrep.
 * @param cadena The string with the text.
 * @param strf The text to find.
 * @param strr The replacement text.
 * @return The text updated wit the replacement.
 */
char * strrep(const char * cadena, const char * strf, const char * strr) {
    char * string;
    char * ptr;
    char * strrep;

    string = (char *)malloc(strlen(cadena) + 1);
    sprintf(string, "%s", cadena);
    if (!*strf) return string;
    ptr = strtokk(string, strf);
    strrep = malloc(strlen(ptr) + 1);
    memset(strrep, 0, strlen(ptr) + 1);
    while (ptr) {
        strrep = appendstr(strrep, ptr);
        ptr = strtokk(NULL, strf);
        if (ptr) strrep = appendstr(strrep, strr);
    }
    free(string);
    return strrep;
}
