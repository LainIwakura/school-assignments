#!/bin/bash

# $# denotes the number of arguments
if [ $# == 0 ]; then
  echo "No arguments passed, try again."
fi

# For each argument in the argument list, denoted by $@
for arg in "$@"
do
  if ! [[ "$arg" =~ ^[0-9]+$ ]]; then # If the argument does not match our regular expression ^[0-9]+$
    echo "$arg is not a number"
  else
    echo "$arg is a number"
  fi
done
