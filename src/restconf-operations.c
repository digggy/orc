//
// Created by digggy on 15.04.21.
//
#include "restconf-operations.h"


struct json_object *get_json_output2yang(char *operation) {
  const map_str2str *iter = json_output2yang;
  const map_str2str *end = json_output2yang + sizeof(json_output2yang) / sizeof(json_output2yang[0]);
  int found = 0;
  while (iter && iter < end) {
    if (strlen(operation) == strlen(iter->key) && strcmp(operation, iter->key) == 0) {
      found = 1;
      break;
    }
    iter++;
  }
  if (!found) {
    return NULL;
  }
  struct json_object *jobj = json_tokener_parse(iter->str);
  return jobj;
}