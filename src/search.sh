#! /bin/bash

if [[ $# -lt 1 ]]; then
    echo "Search term argument not provided. Exiting...";
    exit
fi

sterm=$1;
if [[ $# -ge 2 ]]; then
    files=$(find . | grep "$2");
else
    files=$(find .);
fi

IFS=$'\n';
for file in $files; do
    lines=$(grep -n $sterm $file);
    if [[ ${#lines} -gt 0 ]]; then
        echo $file:;
        for line in $lines; do
            echo "    Line $line";
        done
    fi
done
