#!/bin/sh

for file in $@; do
	sed s/_64//g $file > $(sed s/_64//g <<< "$file")
done
