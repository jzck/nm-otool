#!/bin/sh

for file in $@; do
	sed s/_64//g $@ > $(sed s/_64//g <<< "$@")
done
