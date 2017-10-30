#!/bin/sh

make

##########
# NM
##########

#test_facile
./nmdiff.sh tests/test_facile

#test_moins_facile en 64 et 32
./nmdiff.sh tests/test_moins_facile
./nmdiff.sh tests/test_moins_facile_32-bit

#arguments mutilples
./nmdiff.sh tests/test_facile tests/test_facile

#fichiers objets
./nmdiff.sh objs/ft_nm.o

#bibliotheques dynamiques
./nmdiff.sh 

#biblioteque universelle
./nmdiff.sh


##########
# OTOOL
##########
