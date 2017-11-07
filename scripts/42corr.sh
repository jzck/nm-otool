#!/bin/sh

make

##########
# NM
##########

#test_facile
./scripts/nmdiff.sh tests/test_facile

#test_moins_facile en 64 et 32
./scripts/nmdiff.sh tests/test_moins_facile
./scripts/nmdiff.sh tests/test_moins_facile_32-bit

#arguments mutilples
./scripts/nmdiff.sh tests/test_facile tests/test_facile

#fichiers objets
./scripts/nmdiff.sh objs/ft_nm.o

#bibliotheques dynamiques
./scripts/nmdiff.sh /usr/lib/libcompression.dylib


#biblioteque universelle
./scripts/nmdiff.sh /usr/bin/audiodevice
./scripts/nmdiff.sh /usr/bin/python


##########
# OTOOL
##########

#test_facile
./scripts/otooldiff.sh -t tests/test_facile

#test_moins_facile en 64 et 32
./scripts/otooldiff.sh -t tests/test_moins_facile
./scripts/otooldiff.sh -t tests/test_moins_facile_32-bit

#arguments mutilples
./scripts/otooldiff.sh -t tests/test_facile tests/test_facile

#fichiers objets
./scripts/otooldiff.sh -t objs/ft_nm.o

#bibliotheques dynamiques
./scripts/otooldiff.sh -t /usr/lib/libcompression.dylib

#biblioteque universelle
./scripts/otooldiff.sh -t /usr/bin/audiodevice
./scripts/otooldiff.sh -t /usr/bin/python
