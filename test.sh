#!/bin/bash

BINARY=$1
TEST=$2
BINARY_REF=$3

if [ -z $1 ] || [ -z $2 ]
then
	echo "test [binary] [file ...]"
fi

for the_test in $TEST
do
	$BINARY $the_test > /tmp/my_ref
	$BINARY_REF $the_test > /tmp/ref
	diff /tmp/my_ref /tmp/ref > /dev/null
	VAR=$?
	if [ $VAR -eq 1 ]
	then
		echo "\033[31m[FAILED] $the_test"
	elif [ $VAR -eq 0 ] 
	then
		echo "\033[32m[SUCCES] $the_test"
	fi
done
