#!/bin/bash

# begin our gcd function
gcd () {
  dividend=$1 #the dividend will be the first argument
  divisor=$2  #the divisor will be the second argument

  remainder=1 #just set the remainder to 1 for now

  # loop until the remainder is equal to 0
  until [ "$remainder" -eq 0 ]
  do
    # This is euclid's algorithm
    let "remainder = $dividend % $divisor"
    dividend=$divisor
    divisor=$remainder
  done
}

# If we don't have exactly 2 arguments
if [ "$#" -ne 2 ]
then
  echo "Provide exactly 2 numeric arguments"
  exit 1;
elif ! [[ "$1" =~ ^[0-9]+$ ]]; then # if arg1 is not numeric, using a regex
  echo "Invalid argument: $1"
  exit 1;
elif ! [[ "$2" =~ ^[0-9]+$ ]]; then # if arg2 is not numeric, using a regex
  echo "Invalid argument $2"
  exit 1;
fi

gcd $1 $2
echo $dividend
