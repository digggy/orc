#ifndef RESTCONF_UTIL_H
#define RESTCONF_UTIL_H
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include "cgi.h"

int split_pair_by_char(char *split, char **first, char **second,
                       char split_char);
char *str_dup(const char *c);
char *strn_dup(const char *c, size_t to);
int is_in_vector(char **vec, char *value);
char *concat(const char *string_one, const char *string_two);

char * appendstr(char * string, const char * append);
char * strtokk(char * string, const char * strf);
char * strrep(const char * string, const char * strf, const char * strr);


//char *add_space(char* string);
#endif  // RESTCONF_UTIL_H
