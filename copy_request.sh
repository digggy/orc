#!/bin/bash

parent_path=$( cd "$(dirname "${BASH_SOURCE[0]}")" ; pwd -P )
# cd to the directory of the bash script and get the files in relative location
cd "$parent_path"

REQUEST_METHOD=POST;CONTENT_TYPE=application/yang-data+json;HTTP_ACCEPT=application/yang-data+json;REQUEST_URI=cgi-bin/restconf/operations/openwrt-measurement-operations:mtr;CONTENT_LENGTH=500
#REQUEST_METHOD=POST;CONTENT_TYPE=application/yang-data+json;HTTP_ACCEPT=application/yang-data+json;REQUEST_URI=cgi-bin/restconf/operations/openwrt-system-operations:delete;CONTENT_LENGTH=500
#REQUEST_METHOD=GET;CONTENT_TYPE=application/yang-data+json;HTTP_ACCEPT=application/yang-data+json;REQUEST_URI=cgi-bin/restconf/operations/;CONTENT_LENGTH=0

#echo "
#REQUEST_METHOD= $REQUEST_METHOD
#REQUEST_URI= $REQUEST_URI
#
#HTTP_ACCEPT= $HTTP_ACCEPT
#CONTENT_TYPE= $CONTENT_TYPE
#CONTENT_LENGTH= $CONTENT_LENGTH"

# send request with the env variable set above
REQUEST_METHOD=$REQUEST_METHOD \
CONTENT_TYPE=$CONTENT_TYPE \
HTTP_ACCEPT=$HTTP_ACCEPT \
REQUEST_URI=$REQUEST_URI \
CONTENT_LENGTH=$CONTENT_LENGTH \
 ./cmake-build-debug-openwrt/restconf < /home/digggy/project/openwrt-guide/request.json
