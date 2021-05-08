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
        char *with_semicolon = concat(":", key);
        char *unique_name = concat(iter->key, with_semicolon);
        char *rpc_unique_name = concat(operation_root, unique_name);
        json_object_object_add(all_operation, unique_name,
                               json_object_new_string(rpc_unique_name));

        free(unique_name);
        free(rpc_unique_name);
        free(with_semicolon);
      }
    }
    iter++;
  }
  return supported_operations;
};

char *add_to_command(char *command, char *string) {
  strcat(command, " ");
  strcat(command, string);
  return command;
}

char *add_to_command_infront(char *str1, char *str2) {
  char *p = malloc(strlen(str1) + strlen(str2) +
                   1);  // Allocate memory for the new string
  strcpy(p, str2);      // Copy str2 to the new string
  strcat(p, " ");
  strcat(p, str1);
  return p;
}

char *json_to_command(char *command_with_options,
                      struct json_object *command_json) {
  // check if the operation has a script
  char *script = json_get_string(command_json, YANG_OPERATION_SCRIPT);
  strcpy(command_with_options,
         json_get_string(command_json, YANG_OPERATION_COMMAND));
  // handle the subcommand
  struct json_object *subcommand =
      json_object_object_get(command_json, YANG_OPERATION_SUBCOMMAND);
  json_object_object_foreach(subcommand, key, value) {
    add_to_command(command_with_options,
                   add_to_command(key, (char *)json_object_get_string(value)));
  }
  // handle the flags
  struct json_object *flags = json_get_array(command_json, YANG_OPERATION_FLAG);
  for (int i = 0; i < json_object_array_length(flags); i++) {
    char *flag = "-";
    add_to_command(command_with_options,
                   concat(flag, json_object_get_string(
                                    json_object_array_get_idx(flags, i))));
  }
  // handle the options
  struct json_object *options =
      json_object_object_get(command_json, YANG_OPERATION_OPTION);
  json_object_object_foreach(options, flag, flag_value) {
    char *flag_with_value = "-";
    add_to_command(command_with_options, concat(flag_with_value, flag));
    add_to_command(command_with_options,
                   (char *)json_object_get_string(flag_value));
  }
  // handle other arguments
  struct json_object *args = json_get_array(command_json, YANG_OPERATION_ARGS);
  for (int i = 0; i < json_object_array_length(args); i++) {
    add_to_command(
        command_with_options,
        (char *)json_object_get_string(json_object_array_get_idx(args, i)));
  }

  // If there is script then the script is doing the parsing of the json
  if (script) {
    if (script) {
      char *script_command = "";
      // Format ping -4 -c 5 google.com > /tmp/restconf_tmp &&
      // /root/.restconf/ping_to_json_test.sh

      script_command = concat(script_command, script_path);
      script_command = concat(script_command, script);
      command_with_options =
          add_to_command_infront(command_with_options, script_command);
    }
  }
  return command_with_options;
}