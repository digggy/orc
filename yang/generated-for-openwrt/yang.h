
#ifndef _YANG_H
#define _YANG_H
#include <stddef.h>
#include <json-c/json.h>
#include <string.h>

typedef struct map_str2str{
  char *key;
  char *str;
} map_str2str;

static const map_str2str modulemap[] = {
    {"openwrt-network", "{\"type\": \"module\", \"map\": {\"globals\": {\"type\": \"container\", \"map\": {\"ula_prefix\": {\"type\": \"leaf\", \"option\": \"ula_prefix\", \"leaf-type\": \"inet:ipv6-prefix\"}}, \"section\": \"globals\", \"section-name\": \"globals\", \"depth\": 1}, \"interfaces\": {\"type\": \"container\", \"map\": {\"interface\": {\"type\": \"list\", \"map\": {\"ifname\": {\"type\": \"leaf\", \"option\": \"ifname\", \"leaf-type\": \"string\", \"mandatory\": true}, \"iftype\": {\"type\": \"leaf\", \"option\": \"type\", \"leaf-type\": \"string\"}, \"stp\": {\"type\": \"leaf\", \"option\": \"stp\", \"leaf-type\": \"openwrt-bool\"}, \"bridge_empty\": {\"type\": \"leaf\", \"option\": \"bridge_empty\", \"leaf-type\": \"openwrt-bool\"}, \"igmp_snooping\": {\"type\": \"leaf\", \"option\": \"imgp_snooping\", \"leaf-type\": \"openwrt-bool\"}, \"multicast_querier\": {\"type\": \"leaf\", \"option\": \"multicast_querier\", \"leaf-type\": \"openwrt-bool\"}, \"macaddr\": {\"type\": \"leaf\", \"option\": \"macaddr\", \"leaf-type\": \"yang:phys-address\"}, \"mtu\": {\"type\": \"leaf\", \"option\": \"mtu\", \"leaf-type\": \"int64\"}, \"auto\": {\"type\": \"leaf\", \"option\": \"auto\", \"leaf-type\": \"openwrt-bool\"}, \"ipv6\": {\"type\": \"leaf\", \"option\": \"ipv6\", \"leaf-type\": \"openwrt-bool\"}, \"force_link\": {\"type\": \"leaf\", \"option\": \"force_link\", \"leaf-type\": \"openwrt-bool\"}, \"disabled\": {\"type\": \"leaf\", \"option\": \"disabled\", \"leaf-type\": \"openwrt-bool\"}, \"ip4table\": {\"type\": \"leaf\", \"option\": \"ip4table\", \"leaf-type\": \"string\"}, \"ip6table\": {\"type\": \"leaf\", \"option\": \"ip6table\", \"leaf-type\": \"string\"}, \"proto\": {\"type\": \"leaf\", \"option\": \"proto\", \"leaf-type\": \"string\"}, \"ipaddr\": {\"type\": \"leaf\", \"option\": \"ipaddr\", \"leaf-type\": \"inet:ipv4-address\"}, \"netmask\": {\"type\": \"leaf\", \"option\": \"netmask\", \"leaf-type\": \"inet:ipv4-prefix\"}, \"gateway\": {\"type\": \"leaf\", \"option\": \"gateway\", \"leaf-type\": \"inet:ipv4-address\"}, \"broadcast\": {\"type\": \"leaf\", \"option\": \"broadcast\", \"leaf-type\": \"inet:ipv4-address\"}, \"ip6addr\": {\"type\": \"leaf\", \"option\": \"ip6addr\", \"leaf-type\": \"inet:ipv6-address\"}, \"ip6gw\": {\"type\": \"leaf\", \"option\": \"ip6gw\", \"leaf-type\": \"inet:ipv6-address\"}, \"layer\": {\"type\": \"leaf\", \"option\": \"layer\", \"leaf-type\": {\"leaf-type\": \"uint8\", \"from\": 1, \"to\": 3}}, \"dns\": {\"type\": \"leaf-list\", \"option\": \"dns\", \"leaf-type\": \"inet:ipv4-address\"}}, \"section\": \"interface\", \"keys\": [\"ifname\"], \"mandatory\": [\"ifname\"], \"depth\": 2, \"parent\": \"interfaces\"}}, \"depth\": 1}, \"rules\": {\"type\": \"container\", \"map\": {\"ip4rules\": {\"type\": \"list\", \"map\": {\"mark\": {\"type\": \"leaf\", \"option\": \"mark\", \"leaf-type\": \"string\"}, \"in\": {\"type\": \"leaf\", \"option\": \"in\", \"leaf-type\": \"string\"}, \"out\": {\"type\": \"leaf\", \"option\": \"out\", \"leaf-type\": \"string\"}, \"src\": {\"type\": \"leaf\", \"option\": \"src\", \"leaf-type\": \"inet:ipv4-prefix\"}, \"dest\": {\"type\": \"leaf\", \"option\": \"dest\", \"leaf-type\": \"inet:ipv4-prefix\"}, \"tos\": {\"type\": \"leaf\", \"option\": \"tos\", \"leaf-type\": \"uint64\"}, \"invert\": {\"type\": \"leaf\", \"option\": \"invert\", \"leaf-type\": \"openwrt-bool\"}, \"priority\": {\"type\": \"leaf\", \"option\": \"priority\", \"leaf-type\": \"uint64\"}, \"lookup\": {\"type\": \"leaf\", \"option\": \"lookup\", \"leaf-type\": \"string\"}, \"goto\": {\"type\": \"leaf\", \"option\": \"goto\", \"leaf-type\": \"uint64\"}, \"action\": {\"type\": \"leaf\", \"option\": \"action\", \"leaf-type\": \"string\"}}, \"section\": \"rule\", \"keys\": [\"mark\"], \"depth\": 2, \"parent\": \"rules\"}, \"ip6rules\": {\"type\": \"list\", \"map\": {\"mark\": {\"type\": \"leaf\", \"option\": \"mark\", \"leaf-type\": \"string\"}, \"in\": {\"type\": \"leaf\", \"option\": \"in\", \"leaf-type\": \"string\"}, \"out\": {\"type\": \"leaf\", \"option\": \"out\", \"leaf-type\": \"string\"}, \"src\": {\"type\": \"leaf\", \"option\": \"src\", \"leaf-type\": \"inet:ipv6-prefix\"}, \"dest\": {\"type\": \"leaf\", \"option\": \"dest\", \"leaf-type\": \"inet:ipv6-prefix\"}, \"tos\": {\"type\": \"leaf\", \"option\": \"tos\", \"leaf-type\": \"uint64\"}, \"invert\": {\"type\": \"leaf\", \"option\": \"invert\", \"leaf-type\": \"openwrt-bool\"}, \"priority\": {\"type\": \"leaf\", \"option\": \"priority\", \"leaf-type\": \"uint64\"}, \"lookup\": {\"type\": \"leaf\", \"option\": \"lookup\", \"leaf-type\": \"string\"}, \"goto\": {\"type\": \"leaf\", \"option\": \"goto\", \"leaf-type\": \"uint64\"}, \"action\": {\"type\": \"leaf\", \"option\": \"action\", \"leaf-type\": \"string\"}}, \"section\": \"rule\", \"keys\": [\"mark\"], \"depth\": 2, \"parent\": \"rules\"}}, \"depth\": 1}, \"routes\": {\"type\": \"container\", \"map\": {\"ip4routes\": {\"type\": \"list\", \"map\": {\"name\": {\"type\": \"leaf\", \"option\": \"name\", \"leaf-type\": \"string\"}, \"interface\": {\"type\": \"leaf\", \"option\": \"interface\", \"leaf-type\": \"string\", \"mandatory\": true}, \"target\": {\"type\": \"leaf\", \"option\": \"target\", \"leaf-type\": \"inet:ipv4-address\"}, \"netmask\": {\"type\": \"leaf\", \"option\": \"netmask\", \"leaf-type\": \"inet:ipv4-prefix\"}, \"gateway\": {\"type\": \"leaf\", \"option\": \"gateway\", \"leaf-type\": \"inet:ipv4-address\"}, \"metric\": {\"type\": \"leaf\", \"option\": \"metric\", \"leaf-type\": \"uint64\"}, \"mtu\": {\"type\": \"leaf\", \"option\": \"mtu\", \"leaf-type\": \"uint64\"}, \"table\": {\"type\": \"leaf\", \"option\": \"table\", \"leaf-type\": \"string\"}, \"source\": {\"type\": \"leaf\", \"option\": \"source\", \"leaf-type\": \"inet:ipv4-address\"}, \"onlink\": {\"type\": \"leaf\", \"option\": \"onlink\", \"leaf-type\": \"openwrt-bool\"}, \"rtype\": {\"type\": \"leaf\", \"option\": \"type\", \"leaf-type\": \"string\"}}, \"section\": \"route\", \"keys\": [\"name\"], \"mandatory\": [\"interface\"], \"depth\": 2, \"parent\": \"routes\"}, \"ip6routes\": {\"type\": \"list\", \"map\": {\"name\": {\"type\": \"leaf\", \"option\": \"name\", \"leaf-type\": \"string\"}, \"interface\": {\"type\": \"leaf\", \"option\": \"interface\", \"leaf-type\": \"string\", \"mandatory\": true}, \"target\": {\"type\": \"leaf\", \"option\": \"target\", \"leaf-type\": \"inet:ipv6-address\"}, \"gateway\": {\"type\": \"leaf\", \"option\": \"gateway\", \"leaf-type\": \"inet:ipv6-address\"}, \"metric\": {\"type\": \"leaf\", \"option\": \"metric\", \"leaf-type\": \"uint64\"}, \"mtu\": {\"type\": \"leaf\", \"option\": \"mtu\", \"leaf-type\": \"uint64\"}, \"table\": {\"type\": \"leaf\", \"option\": \"table\", \"leaf-type\": \"string\"}, \"source\": {\"type\": \"leaf\", \"option\": \"source\", \"leaf-type\": \"inet:ipv4-address\"}, \"onlink\": {\"type\": \"leaf\", \"option\": \"onlink\", \"leaf-type\": \"openwrt-bool\"}, \"rtype\": {\"type\": \"leaf\", \"option\": \"type\", \"leaf-type\": \"string\"}}, \"section\": \"route6\", \"keys\": [\"name\"], \"mandatory\": [\"interface\"], \"depth\": 2, \"parent\": \"routes\"}}, \"depth\": 1}, \"switches\": {\"type\": \"container\", \"map\": {\"switch\": {\"type\": \"list\", \"map\": {\"name\": {\"type\": \"leaf\", \"option\": \"name\", \"leaf-type\": \"string\"}, \"reset\": {\"type\": \"leaf\", \"option\": \"reset\", \"leaf-type\": \"openwrt-bool\"}, \"enable_vlan\": {\"type\": \"leaf\", \"option\": \"enable_vlan\", \"leaf-type\": \"openwrt-bool\"}, \"enable_mirror_rx\": {\"type\": \"leaf\", \"option\": \"enable_mirror_rx\", \"leaf-type\": \"openwrt-bool\"}, \"enable_mirror_tx\": {\"type\": \"leaf\", \"option\": \"enable_mirror_tx\", \"leaf-type\": \"openwrt-bool\"}, \"mirror_monitor_port\": {\"type\": \"leaf\", \"option\": \"mirror_monitor_port\", \"leaf-type\": \"uint64\"}, \"mirror_source_port\": {\"type\": \"leaf\", \"option\": \"mirror_source_port\", \"leaf-type\": \"uint64\"}, \"arl_age_time\": {\"type\": \"leaf\", \"option\": \"arl_age_time\", \"leaf-type\": \"uint64\"}, \"igmp_snooping\": {\"type\": \"leaf\", \"option\": \"igmp_snooping\", \"leaf-type\": \"openwrt-bool\"}, \"igmp_v3\": {\"type\": \"leaf\", \"option\": \"igmp_v3\", \"leaf-type\": \"openwrt-bool\"}}, \"section\": \"switch\", \"keys\": [\"name\"], \"depth\": 2, \"parent\": \"switches\"}, \"switch_vlan\": {\"type\": \"list\", \"map\": {\"device\": {\"type\": \"leaf\", \"option\": \"device\", \"leaf-type\": \"string\"}, \"vlan\": {\"type\": \"leaf\", \"option\": \"vlan\", \"leaf-type\": \"uint64\"}, \"vid\": {\"type\": \"leaf\", \"option\": \"vid\", \"leaf-type\": \"uint64\"}, \"ports\": {\"type\": \"leaf-list\", \"option\": \"ports\", \"leaf-type\": \"string\"}}, \"section\": \"switch_vlan\", \"keys\": [\"device\", \"vlan\"], \"depth\": 2, \"parent\": \"switches\"}, \"switch_port\": {\"type\": \"list\", \"map\": {\"device\": {\"type\": \"leaf\", \"option\": \"device\", \"leaf-type\": \"string\"}, \"port\": {\"type\": \"leaf\", \"option\": \"port\", \"leaf-type\": \"uint64\"}, \"pvid\": {\"type\": \"leaf\", \"option\": \"pvid\", \"leaf-type\": \"uint64\"}, \"enable_eee\": {\"type\": \"leaf\", \"option\": \"enable_eee\", \"leaf-type\": \"openwrt-bool\"}, \"igmp_snooping\": {\"type\": \"leaf\", \"option\": \"igmp_snooping\", \"leaf-type\": \"openwrt-bool\"}, \"igmp_v3\": {\"type\": \"leaf\", \"option\": \"igmp_v3\", \"leaf-type\": \"openwrt-bool\"}}, \"section\": \"switch_port\", \"keys\": [\"device\", \"port\"], \"depth\": 2, \"parent\": \"switches\"}}, \"depth\": 1}}, \"package\": \"network\", \"depth\": 0}"},
    {"openwrt-system", "{\"type\": \"module\", \"map\": {\"system\": {\"type\": \"container\", \"map\": {\"hostname\": {\"type\": \"leaf\", \"option\": \"hostname\", \"leaf-type\": \"string\"}, \"buffersize\": {\"type\": \"leaf\", \"option\": \"buffersize\", \"leaf-type\": \"uint32\"}, \"conloglevel\": {\"type\": \"leaf\", \"option\": \"conloglevel\", \"leaf-type\": {\"leaf-type\": \"uint8\", \"from\": 0, \"to\": 7}, \"default\": \"7\"}, \"cronloglevel\": {\"type\": \"leaf\", \"option\": \"cronloglevel\", \"leaf-type\": \"uint8\", \"default\": \"5\"}, \"klogconloglevel\": {\"type\": \"leaf\", \"option\": \"klogconloglevel\", \"leaf-type\": \"uint8\", \"default\": \"7\"}, \"log_buffer_size\": {\"type\": \"leaf\", \"option\": \"lof_buffer_size\", \"leaf-type\": \"uint32\", \"default\": \"16\"}, \"log_file\": {\"type\": \"leaf\", \"option\": \"log_file\", \"leaf-type\": \"string\"}, \"log_hostname\": {\"type\": \"leaf\", \"leaf-type\": \"string\"}, \"log_ip\": {\"type\": \"leaf\", \"option\": \"log_ip\", \"leaf-type\": \"inet:ipv4-address\"}, \"log_port\": {\"type\": \"leaf\", \"option\": \"log_port\", \"leaf-type\": \"uint32\"}, \"log_prefix\": {\"type\": \"leaf\", \"option\": \"log_prefix\", \"leaf-type\": \"string\"}, \"log_proto\": {\"type\": \"leaf\", \"option\": \"log_proto\", \"leaf-type\": {\"leaf-type\": \"string\", \"pattern\": \"^(udp|tcp)$\"}, \"default\": \"udp\"}, \"log_remote\": {\"type\": \"leaf\", \"option\": \"log_remote\", \"leaf-type\": \"boolean\", \"default\": \"false\"}, \"log_size\": {\"type\": \"leaf\", \"option\": \"log_size\", \"leaf-type\": \"uint32\", \"default\": \"16\"}, \"log_trailer_null\": {\"type\": \"leaf\", \"option\": \"log_trailer_null\", \"leaf-type\": \"boolean\", \"default\": \"false\"}, \"log_type\": {\"type\": \"leaf\", \"option\": \"log_type\", \"leaf-type\": {\"leaf-type\": \"string\", \"pattern\": \"^(circular|file)$\"}}, \"urandom_seed\": {\"type\": \"leaf\", \"option\": \"urandom_seed\", \"leaf-type\": \"string\", \"default\": \"0\"}, \"timezone\": {\"type\": \"leaf\", \"option\": \"timezone\", \"leaf-type\": \"string\"}, \"zonename\": {\"type\": \"leaf\", \"option\": \"zonename\", \"leaf-type\": \"string\"}}, \"section-name\": \"OpenWrt\", \"section\": \"system\", \"depth\": 1}, \"ntp\": {\"type\": \"container\", \"map\": {\"enabled\": {\"type\": \"leaf\", \"option\": \"enabled\", \"leaf-type\": {\"leaf-type\": \"string\", \"pattern\": \"^(0|1)$\"}}, \"enable_server\": {\"type\": \"leaf\", \"option\": \"enable_server\", \"leaf-type\": {\"leaf-type\": \"string\", \"pattern\": \"^(0|1)$\"}}, \"server\": {\"type\": \"leaf-list\", \"option\": \"server\", \"leaf-type\": \"string\"}}, \"section\": \"timeserver\", \"section-name\": \"ntp\", \"depth\": 1}}, \"package\": \"system\", \"depth\": 0}"},
    {"openwrt-uci-extension", "{\"type\": \"module\", \"map\": {}, \"depth\": 0}"},
    {"restconf-example", "{\"type\": \"module\", \"map\": {\"course\": {\"type\": \"container\", \"map\": {\"name\": {\"type\": \"leaf\", \"option\": \"name\", \"leaf-type\": \"string\"}, \"semester\": {\"type\": \"leaf\", \"option\": \"semester\", \"leaf-type\": {\"leaf-type\": \"uint8\", \"from\": 1, \"to\": 6}}, \"instructors\": {\"type\": \"leaf-list\", \"option\": \"instructors\", \"leaf-type\": \"string\"}, \"students\": {\"type\": \"list\", \"map\": {\"firstname\": {\"type\": \"leaf\", \"option\": \"firstname\", \"leaf-type\": \"string\"}, \"lastname\": {\"type\": \"leaf\", \"option\": \"lastname\", \"leaf-type\": \"string\"}, \"age\": {\"type\": \"leaf\", \"option\": \"age\", \"leaf-type\": {\"leaf-type\": \"uint8\", \"from\": 0, \"to\": 120}}, \"major\": {\"type\": \"leaf\", \"option\": \"major\", \"leaf-type\": {\"leaf-type\": \"string\", \"pattern\": \"^(CS|IMS)$\"}}, \"grade\": {\"type\": \"leaf\", \"option\": \"grade\", \"leaf-type\": \"grade\"}}, \"section\": \"student\", \"leaf-as-name\": \"lastname\", \"keys\": [\"firstname\", \"lastname\", \"age\"], \"depth\": 2, \"parent\": \"course\"}, \"instructor\": {\"type\": \"container\", \"map\": {\"name\": {\"type\": \"leaf\", \"option\": \"name\", \"leaf-type\": \"string\"}, \"email\": {\"type\": \"leaf\", \"option\": \"email\", \"leaf-type\": \"email\"}}, \"section-name\": \"instructor\", \"section\": \"instructor\", \"depth\": 2, \"parent\": \"course\"}}, \"section-name\": \"course\", \"section\": \"course\", \"depth\": 1}}, \"package\": \"restconf-example\", \"depth\": 0}"},
    {"openwrt-operations", "{\"type\": \"module\", \"map\": {\"copy\": {\"type\": \"rpc\", \"map\": {\"input\": {\"map\": {\"_source\": {\"type\": \"leaf\", \"mandatory\": true, \"leaf-type\": \"string\"}, \"_destination\": {\"type\": \"leaf\", \"mandatory\": true, \"leaf-type\": \"string\"}}, \"mandatory\": [\"_source\", \"_destination\"]}, \"output\": {\"map\": {\"result\": {\"type\": \"leaf\", \"leaf-type\": \"string\"}}}}, \"command-name\": \"cp\"}, \"delete\": {\"type\": \"rpc\", \"map\": {\"input\": {\"map\": {\"_filename\": {\"type\": \"leaf\", \"mandatory\": true, \"leaf-type\": \"string\"}}, \"mandatory\": [\"_filename\"]}, \"output\": {\"map\": {\"result\": {\"type\": \"leaf\", \"leaf-type\": \"string\"}}}}, \"command-name\": \"rm\"}, \"reboot\": {\"type\": \"rpc\", \"map\": {\"input\": {\"map\": {\"delay\": {\"type\": \"leaf\", \"option\": \"d\", \"leaf-type\": \"int32\"}, \"force\": {\"type\": \"leaf\", \"option\": \"f\", \"leaf-type\": \"openwrt-bool\"}}}, \"output\": {\"map\": {\"result\": {\"type\": \"leaf\", \"leaf-type\": \"string\"}}}}, \"command-name\": \"reboot\"}, \"ping\": {\"type\": \"rpc\", \"map\": {\"input\": {\"map\": {\"interval\": {\"type\": \"leaf\", \"leaf-type\": \"int32\", \"default\": \"1\"}, \"count\": {\"type\": \"leaf\", \"leaf-type\": \"int32\", \"default\": \"4\"}, \"quiet\": {\"type\": \"leaf\", \"leaf-type\": \"boolean\", \"default\": \"true\"}}}, \"output\": {\"map\": {\"result\": {\"type\": \"container\", \"map\": {\"summary\": {\"type\": \"container\", \"map\": {\"packets_transmitted\": {\"type\": \"leaf\", \"leaf-type\": \"int32\"}, \"packets_received\": {\"type\": \"leaf\", \"leaf-type\": \"int32\"}, \"packets_lost\": {\"type\": \"leaf\", \"leaf-type\": \"percent\"}, \"time\": {\"type\": \"leaf\", \"leaf-type\": {\"leaf-type\": \"decimal64\", \"fraction-digits\": \"2\"}}}}, \"statistics\": {\"type\": \"container\", \"map\": {\"min\": {\"type\": \"leaf\", \"leaf-type\": {\"leaf-type\": \"decimal64\", \"fraction-digits\": \"2\"}}, \"avg\": {\"type\": \"leaf\", \"leaf-type\": {\"leaf-type\": \"decimal64\", \"fraction-digits\": \"2\"}}, \"max\": {\"type\": \"leaf\", \"leaf-type\": {\"leaf-type\": \"decimal64\", \"fraction-digits\": \"2\"}}, \"mdev\": {\"type\": \"leaf\", \"leaf-type\": {\"leaf-type\": \"decimal64\", \"fraction-digits\": \"2\"}}}}, \"icmp_sequences\": {\"type\": \"list\", \"map\": {\"id\": {\"type\": \"leaf\", \"leaf-type\": \"uint8\"}, \"bytes\": {\"type\": \"leaf\", \"leaf-type\": \"uint8\"}, \"target\": {\"type\": \"leaf\", \"leaf-type\": \"string\"}, \"target_ip\": {\"type\": \"leaf\", \"leaf-type\": \"string\"}, \"icmp_seq\": {\"type\": \"leaf\", \"leaf-type\": \"uint8\"}, \"ttl\": {\"type\": \"leaf\", \"leaf-type\": \"uint8\"}, \"time_taken\": {\"type\": \"leaf\", \"leaf-type\": {\"leaf-type\": \"decimal64\", \"fraction-digits\": \"2\"}}}, \"keys\": [\"id\"]}}}}}}, \"command-name\": \"ping\"}, \"mtr\": {\"type\": \"rpc\", \"map\": {\"input\": {\"map\": {\"report\": {\"type\": \"leaf\", \"leaf-type\": {\"leaf-type\": \"string\", \"pattern\": \"^(r)$\"}, \"flag\": \"r\", \"default\": \"r\"}, \"json\": {\"type\": \"leaf\", \"leaf-type\": {\"leaf-type\": \"string\", \"pattern\": \"^(j)$\"}, \"flag\": \"j\", \"default\": \"j\"}, \"destination\": {\"type\": \"leaf\", \"mandatory\": true, \"leaf-type\": \"inet:host\"}, \"interval\": {\"type\": \"leaf\", \"leaf-type\": \"int32\", \"option\": \"i\", \"default\": \"1\"}, \"count\": {\"type\": \"leaf\", \"leaf-type\": \"int32\", \"option\": \"c\", \"default\": \"4\"}, \"test_decimal\": {\"type\": \"leaf\", \"leaf-type\": {\"leaf-type\": \"decimal64\", \"fraction-digits\": \"2\"}, \"default\": \"4.0\"}}, \"mandatory\": [\"destination\"]}, \"output\": {\"map\": {\"report\": {\"type\": \"container\", \"map\": {\"mtr\": {\"type\": \"container\", \"map\": {\"source\": {\"type\": \"leaf\", \"leaf-type\": \"string\"}, \"destination\": {\"type\": \"leaf\", \"leaf-type\": \"string\"}, \"type-of-service\": {\"type\": \"leaf\", \"leaf-type\": \"string\"}, \"packet-size\": {\"type\": \"leaf\", \"leaf-type\": \"uint8\"}, \"bitpattern\": {\"type\": \"leaf\", \"leaf-type\": \"string\"}, \"tests\": {\"type\": \"leaf\", \"leaf-type\": \"uint8\"}}}, \"hubs\": {\"type\": \"list\", \"map\": {\"count\": {\"type\": \"leaf\", \"leaf-type\": \"uint8\"}, \"host\": {\"type\": \"leaf\", \"leaf-type\": \"string\"}, \"loss-percent\": {\"type\": \"leaf\", \"leaf-type\": {\"leaf-type\": \"decimal64\", \"fraction-digits\": \"2\"}}, \"sent\": {\"type\": \"leaf\", \"leaf-type\": \"uint8\"}, \"last\": {\"type\": \"leaf\", \"leaf-type\": {\"leaf-type\": \"decimal64\", \"fraction-digits\": \"2\"}}, \"average-rtt\": {\"type\": \"leaf\", \"leaf-type\": {\"leaf-type\": \"decimal64\", \"fraction-digits\": \"2\"}}, \"best-rtt\": {\"type\": \"leaf\", \"leaf-type\": {\"leaf-type\": \"decimal64\", \"fraction-digits\": \"2\"}}, \"worst-rtt\": {\"type\": \"leaf\", \"leaf-type\": {\"leaf-type\": \"decimal64\", \"fraction-digits\": \"2\"}}, \"standard-deviation\": {\"type\": \"leaf\", \"leaf-type\": {\"leaf-type\": \"decimal64\", \"fraction-digits\": \"2\"}}}, \"keys\": [\"count\"]}}}}}}, \"command-name\": \"mtr -r -j\"}, \"opkg\": {\"type\": \"rpc\", \"map\": {\"input\": {\"map\": {}}, \"output\": {\"map\": {\"result\": {\"type\": \"leaf\", \"leaf-type\": \"string\"}}}}, \"command-name\": \"opkg\"}}, \"depth\": 0}"}
};

static const map_str2str yang2regex[] = {
    {"openwrt-bool", "{\"leaf-type\": \"string\", \"pattern\": \"^(0|1)$\"}"},
    {"grade", "{\"leaf-type\": \"uint8\", \"from\": 0, \"to\": 100}"},
    {"email", "{\"leaf-type\": \"string\", \"pattern\": \"^[A-Za-z0-9]*@university.de$\"}"},
    {"percent", "{\"leaf-type\": \"uint8\", \"from\": 0, \"to\": 100}"},
    {"inet:host", "{\"leaf-type\": \"union\", \"subtypes\": [{\"pattern\": \"^(([0-9]|[1-9][0-9]|1[0-9][0-9]|2[0-4][0-9]|25[0-5])\\\\.){3}([0-9]|[1-9][0-9]|1[0-9][0-9]|2[0-4][0-9]|25[0-5])(%[\\\\p{N}\\\\p{L}]+)?$\", \"leaf-type\": \"string\"}, {\"pattern\": \"^((:|[0-9a-fA-F]{0,4}):)([0-9a-fA-F]{0,4}:){0,5}((([0-9a-fA-F]{0,4}:)?(:|[0-9a-fA-F]{0,4}))|(((25[0-5]|2[0-4][0-9]|[01]?[0-9]?[0-9])\\\\.){3}(25[0-5]|2[0-4][0-9]|[01]?[0-9]?[0-9])))(%[\\\\p{N}\\\\p{L}]+)?$\", \"leaf-type\": \"string\"}, {\"pattern\": \"^(([^:]+:){6}(([^:]+:[^:]+)|(.*\\\\..*)))|((([^:]+:)*[^:]+)?::(([^:]+:)*[^:]+)?)(%.+)?$\", \"leaf-type\": \"string\"}, {\"pattern\": \"^((([a-zA-Z0-9_]([a-zA-Z0-9\\\\-_]){0,61})?[a-zA-Z0-9]\\\\.)*([a-zA-Z0-9_]([a-zA-Z0-9\\\\-_]){0,61})?[a-zA-Z0-9]\\\\.?)|\\\\.$\", \"leaf-type\": \"string\"}]}"}
};

typedef enum yang_type {
  NONE,
  BINARY,
  BITS,
  BOOLEAN,
  DECIMAL_64,
  EMPTY,
  ENUMERATION,
  IDENTITY_REF,
  INSTANCE_IDENTIFIER,
  INT_8,
  INT_16,
  INT_32,
  INT_64,
  LEAF_REF,
  STRING,
  UINT_8,
  UINT_16,
  UINT_32,
  UINT_64,
  UNION
} yang_type;

struct map_str2yang_type {
  char* str;
  yang_type type;
};
typedef struct map_str2yang_type map_str2yang_type;

static const map_str2yang_type str2yang_type[] = {
    {"string", STRING},
    {"int8", INT_8},
    {"int16", INT_16},
    {"int32", INT_32},
    {"int64", INT_64},
    {"uint8", UINT_8},
    {"uint16", UINT_16},
    {"uint32", UINT_32},
    {"uint64", UINT_64},
    {"binary", BINARY},
    {"boolean", BOOLEAN},
    {"decimal64", DECIMAL_64},
    {"enumeration", ENUMERATION},
    {"union", UNION},
    {"bits", BITS},
    {"yang:xpath1.0", STRING},
    {"counter32", INT_32},
    {"leafref", LEAF_REF},
    {"empty", EMPTY}
};

struct json_object* yang_module_exists(char* module);
yang_type str_to_yang_type(const char* str);
const char* yang_for_type(const char* type);

#endif