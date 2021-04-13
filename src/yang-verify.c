#include "yang-verify.h"
#include <regex.h>
#include "restconf-json.h"
#include "restconf.h"
#include "util.h"
#include "vector.h"
#include "yang-util.h"

static int yang_verify_value_type(struct json_object* type, const char* value);

/**
 * @brief verify JSON leaf
 * @param leaf the JSON leaf to be verified
 * @param yang the YANG leaf node
 * @return error if not verified
 */
error yang_verify_leaf(struct json_object* leaf, struct json_object* yang) {
  const char* value = NULL;
  struct json_object* type = NULL;
  json_type value_type = json_object_get_type(leaf);

  if (value_type == json_type_object || value_type == json_type_array) {
    return INVALID_TYPE;
  }

  json_object_object_get_ex(yang, YANG_LEAF_TYPE, &type);
  if (!type) {
    return YANG_SCHEMA_ERROR;
  }

  if (!(value = json_object_get_string(leaf))) {
    return INVALID_TYPE;
  }
  if (yang_verify_value_type(type, value)) {
    return INVALID_TYPE;
  }
  return RE_OK;
}

/**
 * @brief verify JSON leaf-list
 * @param list the JSON leaf-list to be verified
 * @param yang the YANG leaf-list node
 * @return error if not verified
 */
error yang_verify_leaf_list(struct json_object* list,
                            struct json_object* yang) {
  struct json_object* type = NULL;
  json_type value_type = json_object_get_type(list);
  if (value_type != json_type_array) {
    return INVALID_TYPE;
  }

  json_object_object_get_ex(yang, YANG_LEAF_TYPE, &type);
  if (!type) {
    return YANG_SCHEMA_ERROR;
  }
  for (int i = 0; i < json_object_array_length(list); i++) {
    const char* value = NULL;
    struct json_object* item = json_object_array_get_idx(list, i);
    if (!(value = json_object_get_string(item))) {
      return INVALID_TYPE;
    }
    if (yang_verify_value_type(type, value)) {
      return INVALID_TYPE;
    }
    for (int compare = i + 1; compare < json_object_array_length(list);
         compare++) {
      const char* compare_value = NULL;
      struct json_object* compare_item =
          json_object_array_get_idx(list, compare);
      if (!(compare_value = json_object_get_string(compare_item))) {
        return INVALID_TYPE;
      }
      if (strcmp(value, compare_value) == 0) {
        return IDENTICAL_KEYS;
      }
    }
  }
  return RE_OK;
}

/**
 * @brief verify JSON type again YANG type
 * @param type the yang_type
 * @param val_type the json_type
 * @return 1 if incorrect else 0
 */
int yang_verify_json_type(yang_type type, json_type val_type) {
  switch (type) {
    case BOOLEAN:
      if (val_type != json_type_boolean) return 1;
      break;
    case EMPTY:
      if (val_type != json_type_null) return 1;
      break;
    case IDENTITY_REF:
      break;
    case INT_8:
    case INT_16:
    case INT_32:
    case UINT_8:
    case UINT_16:
    case UINT_32:
      if (val_type != json_type_int) return 1;
      break;
    case LEAF_REF:
      break;
    case UINT_64:
    case INT_64:
      if (val_type != json_type_string && val_type != json_type_int) return 1;
      break;
    case DECIMAL_64:
    case ENUMERATION:
    case BITS:
    case BINARY:
    case STRING:
    case INSTANCE_IDENTIFIER:
      if (val_type != json_type_string) return 1;
      break;
    case UNION:
      break;
    default:
      return 0;
  }
  return 0;
}

/**
 * @brief check if YANG node is mandatory
 * @param yang the YANG node
 * @return 1 if mandatory else 0
 */
int yang_mandatory(struct json_object* yang) {
  const char* type_string = NULL;
  type_string = json_get_string(yang, YANG_TYPE);
  if (!type_string || yang_is_leaf(type_string)) {
    struct json_object* mandatory = NULL;
    json_object_object_get_ex(yang, YANG_MANDATORY, &mandatory);
    if (mandatory && json_object_get_boolean(mandatory)) {
      return 1;
    }
  }
  return 0;
}

/**
 * @brief verify string with regex
 * @param regex the regex
 * @param value the string to be checked
 * @return 1 if error else 0
 */
static int regex_verify_value(const char* regex, const char* value) {
  regex_t regex_o;
  if (regcomp(&regex_o, regex, REG_EXTENDED)) {
    return 1;
  }
  if (regexec(&regex_o, value, 0, NULL, 0)) {
    regfree(&regex_o);
    return 1;
  }
  regfree(&regex_o);
  return 0;
}

/**
 * @brief verify a value against a imported type
 * @param type the name of the type
 * @param value the string value
 * @return 0 if verified else 1
 */
static int verify_value_from_imported(const char* type, const char* value) {
  enum json_tokener_error err;
  const char* typedefinition = yang_for_type((char*)type);
  if (!typedefinition) {
    return 1;
  }
  struct json_object* type_object =
      json_tokener_parse_verbose(typedefinition, &err);
  if (!type_object) {
    return 1;
  }
  int wrong_format = yang_verify_value_type(type_object, value);
  if (wrong_format) {
    json_object_put(type_object);
    return 1;
  }
  json_object_put(type_object);
  return 0;
}

/**
 * @brief verify string value by type object
 * @param type the type object
 * @param value the string value
 * @return 0 if verified else 0
 */

int has_decimal(const char* str) {
  int decimalCheck = 0;
  if (strchr(str, '.') != NULL) {
    decimalCheck = 1;
  }
  return decimalCheck;
}
static int yang_verify_value_type(struct json_object* type, const char* value) {
  const char* leaf_type = NULL;
  int is_object = 0;

  enum other_check { NONE, RANGE, PATTERN, FRACTION_DIGITS } verify_type = NONE;
  if (json_object_get_type(type) == json_type_object) {
    leaf_type = json_get_string(type, YANG_LEAF_TYPE);
    is_object = 1;
  } else {
    leaf_type = json_object_get_string(type);
  }
  yang_type converted = str_to_yang_type(leaf_type);
  switch (converted) {
    case BOOLEAN:
      if (strcmp(value, "true") != 0 && strcmp(value, "false") != 0) return 1;
      break;
    case EMPTY:
      break;
    case IDENTITY_REF:
      break;
    case INT_8: {
      verify_type = RANGE;
      if (has_decimal(value)) {
        return 1;
      };
      int integer = strtoimax(value, NULL, 10);
      if (integer < -128 || integer > 127) return 1;
      break;
    }
    case INT_16: {
      verify_type = RANGE;
      if (has_decimal(value)) {
        return 1;
      };
      int integer = strtoimax(value, NULL, 10);
      if (integer < -32768 || integer > 32767) return 1;
      break;
    }
    case INT_32: {
      verify_type = RANGE;
      if (has_decimal(value)) {
        return 1;
      };
      int integer = strtoimax(value, NULL, 10);
      if (integer < -2147483648 || integer > 2147483647) return 1;
      break;
    }
    case UINT_8: {
      verify_type = RANGE;
      if (has_decimal(value)) {
        return 1;
      };
      int integer = strtoimax(value, NULL, 10);
      if (integer < 0 || integer > 255) return 1;
      break;
    }
    case UINT_16: {
      verify_type = RANGE;
      if (has_decimal(value)) {
        return 1;
      };
      int integer = strtoimax(value, NULL, 10);
      if (integer < 0 || integer > 65535) return 1;
      break;
    }
    case UINT_32: {
      verify_type = RANGE;
      if (has_decimal(value)) {
        return 1;
      };
      int integer = strtoimax(value, NULL, 10);
      if (integer < 0) return 1;
      break;
    }
    case LEAF_REF:
      break;
    case UINT_64: {
      verify_type = RANGE;
      unsigned long integer = strtol(value, NULL, 10);
      if (integer < 0 || integer > 18446744073709551615u) return 1;
      break;
    }
    case INT_64:
      verify_type = RANGE;
      if (has_decimal(value)) {
        return 1;
      };
      break;
    case DECIMAL_64:
      verify_type = FRACTION_DIGITS;

    case ENUMERATION:
    case BITS:
    case INSTANCE_IDENTIFIER:
      break;
    case STRING:
      verify_type = PATTERN;
      break;
    case UNION:
      break;
    default:
      return verify_value_from_imported(leaf_type, value);
  }
  if (is_object) {
    switch (verify_type) {
      case RANGE: {
        const char* from_string = NULL;
        const char* to_string = NULL;
        from_string = json_get_string(type, "from");
        to_string = json_get_string(type, "to");
        if (!from_string || !to_string) {
          break;
        }
        long from = strtol(from_string, NULL, 10);
        long to = strtol(to_string, NULL, 10);
        long integer = strtol(value, NULL, 10);
        if (integer < from || integer > to) {
          return 1;
        }
        break;
      }
      case PATTERN: {
        struct json_object* patterns = NULL;
        json_object_object_get_ex(type, "pattern", &patterns);
        if (json_object_get_type(patterns) == json_type_string) {
          const char* pattern = json_object_get_string(patterns);
          if (regex_verify_value(pattern, value)) {
            return 1;
          } else {
            break;
          }
        } else if (json_object_get_type(patterns) != json_type_array) {
          return 1;
        }
        if (json_object_array_length(patterns) == 0) {
          break;
        }
        json_array_forloop(patterns, index) {
          const char* pattern = json_object_get_string(
              json_object_array_get_idx(patterns, index));
          if (!regex_verify_value(pattern, value)) {
            break;
          }
        }
        return 1;
      }
      case FRACTION_DIGITS: {
        int exists;
        struct json_object* jo_temp = NULL;
        char* before_decimal = NULL;
        char* after_decimal = NULL;
        exists =
            json_object_object_get_ex(type, YANG_FRACTION_DIGITS, &jo_temp);
        if (!exists) {
          return 1;
        }
        int fraction_digits = json_object_get_int64(jo_temp);
        split_pair_by_char(value, &before_decimal, &after_decimal, '.');
        if (strlen(after_decimal) != fraction_digits) {
          return 1;
        }
      }
      default:
        break;
    }
  }
  return 0;
}

error yang_verify_container(struct json_object* content_container,
                            struct json_object* yang) {
  int error;
  const char* value = NULL;
  json_type value_type = json_object_get_type(content_container);

  if (value_type != json_type_object) {
    return INVALID_TYPE;
  }
  error = yang_verify_output(content_container, yang);
  return RE_OK;
};

error yang_verify_list(struct json_object* content_list,
                       struct json_object* yang) {
  return RE_OK;
};

struct command_arguments* yang_verify_input(struct json_object* content_object,
                                            struct json_object* input_child) {
  int mandatory_exist = 1;
  struct json_object* yang = json_get_objects_from_map(input_child);
  if (!yang) {
    return YANG_SCHEMA_ERROR;
  }
  error err;
  // struct that we return to the program
  command_arguments* cmd = malloc(sizeof(command_arguments));
  if (!cmd) {
    fprintf(stderr, "Memory allocation failed");
    return NULL;
  }
  cmd->command = NULL;
  cmd->error = RE_OK;

  {
    // Check if the stdin has the mandatory items
    struct json_object* mandatory = NULL;
    if (!(mandatory = json_get_array(input_child, YANG_MANDATORY))) {
      mandatory_exist = 0;
    } else {
      for (int j = 0; j < json_object_array_length(mandatory); j++) {
        int exists = 0;
        char* mandatory_key = NULL;
        struct json_object* jo_mandatory_key = NULL;
        struct json_object* jo_mandatory_node = NULL;
        jo_mandatory_key = json_object_array_get_idx(mandatory, j);
        mandatory_key = (char*)json_object_get_string(jo_mandatory_key);
        // check if the mandatory field exists
        exists = json_object_object_get_ex(content_object, mandatory_key,
                                           &jo_mandatory_node);
        if (!exists) {
          cmd->error = MANDATORY_NOT_PRESENT;
          return cmd;
        }
      }
    }
  }

  json_object_object_foreach(content_object, key, content_json_value) {
    int exists;
    struct json_object* yang_node;

    const char* yang_node_type = NULL;
    char* flag_with_value = "";
    /*
     * TODO iterate through yang to check if there are any mandatory nodes and
     * check if they are present in content_json_value
     */

    exists = json_object_object_get_ex(yang, key, &yang_node);
    if (exists) {
      yang_node_type = json_get_string(yang_node, YANG_TYPE);
      if (yang_is_leaf(yang_node_type)) {
        // leaf doesnt have any child so do a validation check
        struct json_object* flag_name;
        if ((err = yang_verify_leaf(content_json_value, yang_node)) != RE_OK) {
          cmd->error = err;
          return cmd;
        }
        if (json_object_object_get_ex(yang_node, YANG_OPERATION_FLAG,
                                      &flag_name)) {
          flag_with_value = concat("-", json_object_get_string(flag_name));
          strcat(flag_with_value, " ");
        }
        // adding the actuall value that comes from the input
        flag_with_value =
            concat(flag_with_value, json_object_get_string(content_json_value));
        vector_push_back(cmd->command, flag_with_value);

      } else if (yang_is_leaf_list(yang_node_type)) {
        // leaf-list doesnt have any child so do a validation check
        if ((err = yang_verify_leaf_list(content_json_value, yang_node)) !=
            RE_OK) {
          cmd->error = err;
          return cmd;
        }
        // printf("leaf-list verified\n");
      } else if (yang_is_container(yang_node_type)) {
        // container has children so further validation check
        // printf("It is container\n");
      } else if (yang_is_list(yang_node_type)) {
        // list has children so further validation checks to its elements
        // printf("It is list\n");
      }
    } else {
      // doesnt key doesnt exists
      cmd->error = NO_SUCH_ELEMENT;
      return cmd;
    }
  }
  //  options = command_options;
  return cmd;
}

error yang_verify_output(struct json_object* content_object,
                         struct json_object* output_child) {
  //
  int mandatory_exist = 1;
  struct json_object* yang = json_get_objects_from_map(output_child);
  if (!yang) {
    return YANG_SCHEMA_ERROR;
  }

  error err;

  {
    // Check if the stdin has the mandatory items
    struct json_object* mandatory = NULL;
    if (!(mandatory = json_get_array(output_child, YANG_MANDATORY))) {
      mandatory_exist = 0;
    } else {
      for (int j = 0; j < json_object_array_length(mandatory); j++) {
        int exists = 0;
        char* mandatory_key = NULL;
        struct json_object* jo_mandatory_key = NULL;
        struct json_object* jo_mandatory_node = NULL;
        jo_mandatory_key = json_object_array_get_idx(mandatory, j);
        mandatory_key = (char*)json_object_get_string(jo_mandatory_key);
        // check if the mandatory field exists
        exists = json_object_object_get_ex(content_object, mandatory_key,
                                           &jo_mandatory_node);
        if (!exists) {
          return MANDATORY_NOT_PRESENT;
        }
      }
    }
  }

  json_object_object_foreach(content_object, key, content_json_value) {
    int exists;
    struct json_object* yang_node;

    const char* yang_node_type = NULL;
    /*
     * TODO iterate through yang to check if there are any mandatory nodes and
     * check if they are present in content_json_value
     */
    //    printf("key -> %s\n", key);

    exists = json_object_object_get_ex(yang, key, &yang_node);
    if (exists) {
      yang_node_type = json_get_string(yang_node, YANG_TYPE);

      if (yang_is_leaf(yang_node_type)) {
        // leaf doesnt have any child so do a validation check
        printf("--------------------- LEAF -> %s \n", key);
        if ((err = yang_verify_leaf(content_json_value, yang_node)) != RE_OK) {
          return err;
        }
      } else if (yang_is_leaf_list(yang_node_type)) {
        // leaf-list doesnt have any child so do a validation check
        printf("--------------------- LEAF LIST -> %s \n", key);
        if ((err = yang_verify_leaf_list(content_json_value, yang_node)) !=
            RE_OK) {
          return err;
        }
      } else if (yang_is_container(yang_node_type)) {
        // container has children so further validation check
        printf("--------------------- CONTAINTER -> %s \n", key);
        err = yang_verify_container(content_json_value, yang_node);

      } else if (yang_is_list(yang_node_type)) {
        printf("--------------------- LIST -> %s \n", key);
        // list has children so further validation checks to its elements
        // printf("It is list\n");
      }
    } else {
      // key doesnt exists
      return NO_SUCH_ELEMENT;
    }
  }

  return RE_OK;
}
