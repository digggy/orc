//
// Created by Malte Granderath on 03/09/2019.
//

#include "yang-util.h"
#include <string.h>

int yang_is_leaf(const char* type_string) {
  return strcmp(type_string, YANG_LEAF) == 0;
}

int yang_is_list(const char* type_string) {
  return strcmp(type_string, YANG_LIST) == 0;
}

int yang_is_leaf_list(const char* type_string) {
  return strcmp(type_string, YANG_LEAF_LIST) == 0;
}

int yang_is_container(const char* type_string) {
  return strcmp(type_string, YANG_CONTAINER) == 0;
}

int yang_is_rpc(const char* type_string) {
  return strcmp(type_string, YANG_RPC) == 0;
}

int yang_is_input(const char* type_string) {
  return strcmp(type_string, YANG_INPUT) == 0;
}

int yang_is_output(const char* type_string) {
  return strcmp(type_string, YANG_OUTPUT) == 0;
}

int yang_is_choice(const char* type_string) {
    return strcmp(type_string, YANG_CHOICE) == 0;
}
