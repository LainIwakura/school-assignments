#!/bin/bash

num=$1

if [ -z $num ]; then
  echo "No arguments passed."
  exit 1
fi

function isValid()
{
  if ! [[ "$1" =~ ^[0-9]+(.[0-9]+)?$ ]]; then
    echo "Number is not valid"
    return 1
  elif [[ "$1" =~ ^[0-9]+$ ]]; then
    echo "Number is a natural number."
    return 0
  elif [[ "$1" =~ ^[0-9]+.[0-9]+$ ]]; then
    echo "Number is a real number."
    return 0
  fi
}

if ! isValid $num; then
  exit 1
fi

parts=($(echo -n $num | tr '.' ' '))

echo "Digits before the decimal point: $(echo -n ${parts[0]} | wc -c)"
echo "Digits after the decimal point: $(echo -n ${parts[1]} | wc -c)"
