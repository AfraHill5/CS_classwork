#!/bin/sh

if [ $# -ne 3 ]
then
    echo "Needs to be 3 input numbers."
else
    let a=$1
    let b=$2
    let c=$3
    if [ $a -gt $b ] && [ $1 -gt $c ]
    then
        echo $a is biggest.
    elif [ $b -gt $a ] && [ $b -gt $c ] 
    then 
        echo $b is biggest.
    else
        echo $c is biggest.
    fi
fi
