#!/bin/bash

declare -a f_array=("ietf-yang-types" "ietf-interfaces" "ietf-inet-types" "openwrt-network" "openwrt-system" "openwrt-uci-extension" "restconf-example")

for val in ${f_array[@]}; do
    echo "pyang -f yin ./$val.yang -p ./ -o ./yin/$val.yin"
    pyang -f yin ./$val.yang -p ./ -o ./yin/$val.yin
done


all_files=""
declare -a openwrt_f_array=("${f_array[@]:3:4}")

#echo "${openwrt_f_array[@]}"
for val in ${openwrt_f_array[@]}; do
    all_files+="./yin/$val.yin "
done

echo "python3 ./yin2json/yin2json.py -y ./yin -o /yin2json/generated/ $all_files"
python3 ./yin2json/yin2json.py -y ./yin/ -o ./yin2json/generated/ $all_files