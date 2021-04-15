//
// Created by digggy on 15.04.21.
//
#include "restconf-operations.h"
#include <stdio.h>
#include "restconf-json.h"
#include "util.h"

struct json_object *get_json_output2yang(char *operation) {
  const map_str2str *iter = json_output2yang;
  const map_str2str *end =
      json_output2yang + sizeof(json_output2yang) / sizeof(json_output2yang[0]);
  int found = 0;
  while (iter && iter < end) {
    if (strlen(operation) == strlen(iter->key) &&
        strcmp(operation, iter->key) == 0) {
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

struct json_object *get_all_operations() {
  const map_str2str *iter = modulemap;
  struct json_object *module = NULL;
  struct json_object *module_contents = NULL;
  const map_str2str *end = modulemap + sizeof(modulemap) / sizeof(modulemap[0]);

  struct json_object *supported_operations;
  char *operation_root = "/restconf/operations/";
  char *supported_operations_str =
      "{\n"
      "  \"openwrt-restconf:operations\": {}\n"
      "}";
  supported_operations = json_tokener_parse(supported_operations_str);
  struct json_object *all_operation = NULL;
  json_object_object_get_ex(supported_operations, "openwrt-restconf:operations",
                            &all_operation);
  while (iter && iter < end) {
    module = json_tokener_parse(iter->str);
    if (!module) {
      return NULL;
    }
    module_contents = json_get_objects_from_map(module);
    json_object_object_foreach(module_contents, key, value) {
      const char *type = json_get_string(value, YANG_TYPE);
      if (strlen(YANG_RPC) == strlen(type) && strcmp(YANG_RPC, type) == 0) {
        char *unique_name = concat(iter->key, concat(":", key));
        json_object_object_add(
            all_operation, unique_name,
            json_object_new_string(concat(operation_root, unique_name)));
      }
    }
    iter++;
  }
  return  supported_operations;

};