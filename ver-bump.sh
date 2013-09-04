#!/bin/sh
if [ "$1" = "patch" ]; then
    cmake  -DBUMP:str=1 -P ver-bump.cmake
elif [ "$1" = "minor" ]; then
    cmake -DBUMP:str=2 -P ver-bump.cmake
elif [ "$1" = "major" ]; then
    cmake  -DBUMP:str=3 -P ver-bump.cmake
else
    cmake  -DBUMP:str=0 -P ver-bump.cmake
fi

