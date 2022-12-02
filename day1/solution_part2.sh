#!/bin/bash

  awk NF=NF FS='\n' RS='' input.txt \
| sed 's/ /+/g' \
| bc \
| sort -h \
| tail -n3  \
| awk NF=NF RS='' \
| sed 's/ /+/g' \
| bc \
