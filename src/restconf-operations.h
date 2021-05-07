//
// Created by digggy on 15.04.21.
//

#ifndef RESTCONF_RESTCONF_OPERATIONS_H
#define RESTCONF_RESTCONF_OPERATIONS_H

#include <stddef.h>
#include <json-c/json.h>
#include <string.h>
#include "./generated/yang.h"
#include "yang-util.h"

static const map_str2str json_output2yang[] = {
    {"mtr", "{\n"
     "  \"src\": \"source\",\n"
     "  \"dst\": \"destination\",\n"
     "  \"tos\": \"type-of-service\",\n"
     "  \"psize\": \"packet-size\",\n"
     "  \"Loss%\": \"loss-percent\",\n"
     "  \"Snt\": \"sent\",\n"
     "  \"Last\": \"last\",\n"
     "  \"Avg\": \"average-rtt\",\n"
     "  \"Best\": \"best-rtt\",\n"
     "  \"Wrst\": \"worst-rtt\",\n"
     "  \"StDev\": \"standard-deviation\"\n"
     "}"}
};
static const char* script_path = "/usr/libexec/orc";
static char* default_message = "RPC request successful";
static const char system_commands [3][50] = {"copy", "delete", "reboot"};

struct json_object *get_json_output2yang(char *operation);
struct json_object *get_all_operations();
char* add_to_command(char* command, char* string);
char *json_to_command(char *command_with_options,
                      struct json_object *command_json);

#endif  // RESTCONF_RESTCONF_OPERATIONS_H
