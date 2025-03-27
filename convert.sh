#!/bin/bash

if [ $# -ne 1 ]; then
    echo "Usage: $0 <filename>"
    exit 1
fi

filename="$1"

enscript -C --margins=50:50:50:50 "$filename" -o "$filename.ps"
ps2pdf "$filename.ps"
