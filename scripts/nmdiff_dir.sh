#!/bin/sh

for file in $@/*; do
	printf "%-40s" $file
	./nmdiff.sh $file 2>&-
done
