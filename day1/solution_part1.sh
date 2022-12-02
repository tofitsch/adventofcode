#!/bin/bash

awk NF=NF FS='\n' RS='' input.txt \
| sed 's/ /+/g' \
| bc \
| sort -h \
| tail -n1
