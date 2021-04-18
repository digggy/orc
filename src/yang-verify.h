#ifndef RESTCONF_YANG_VERIFY_H
#define RESTCONF_YANG_VERIFY_H

#include <generated/yang.h>
#include <json-c/json.h>
#include <stdio.h>
#include "error.h"

static char* command_args = "{\n"
    "  \"sub-command\": {},\n"
    "  \"command-flag\": [],\n"
    "  \"command-option\": {},\n"
    "  \"arguments\": []\n"
    "}";

struct command_arguments {
  struct json_object *command_args_json;
  error error;
};

typedef struct command_arguments command_arguments;

error yang_verify_leaf(struct json_object* leaf, struct json_object* yang);
error yang_verify_leaf_list(struct json_object* list, struct json_object* yang);

error yang_verify_container(struct json_object* content_container, struct json_object* yang);

error yang_verify_output(struct json_object* object,
                         struct json_object* yang);
struct command_arguments* yang_verify_input(struct json_object* object,
                                            struct json_object* yang);


int yang_verify_json_type(yang_type type, json_type val_type);
int yang_mandatory(struct json_object* yang);


#endif  // RESTCONF_YANG_VERIFY_H
