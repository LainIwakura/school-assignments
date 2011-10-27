#!/bin/bash

# Our recursive factorial function
factorial () {
  # the function variable number is equal to the first argument passed.
  local number=$1
  if [ "$number" -eq 1 ] # If that number is 1, the result is 1 and we return
  then
    res=1
    return
  fi

  # A temporary variable, holding the argument passed - 1
  (( tmp=$1-1 ))
  factorial $tmp # Calculate the factorial of this part. This is recursion

  (( res=$res * $1 )) #The result is equal to the result times the first argument.
}

# Check for the number of arguments
if [ "$#" -ne 1 ]; then
  echo "Wrong number of arguments"
  exit 1
elif ! [[ "$1" =~ ^[0-9]+$ ]]; then #Check we have a numeric argument
  echo "Argument in wrong format"
  exit 1
fi

# Function call
factorial $1 
echo "$res" # print result
