#!/bin/bash
echo "Good morning: This is my first shell script"
today = `date`;
echo "Today is $today"
dateFields = (`date`)
echo "Total field count is ${#dateFields[@]}"
for field in ${dateFields[@]}
do
  echo $field
done

echo "Month = ${dateFields[1]}"
echo "Time = ${dateFields[3]}"
echo "========================"
echo "Let's try some math"
echo -n "Type a number"
read a
echo -n "Type another number"
read b

sum = $(($a+$b))
echo = "a + b = $sum"

if ((a == b)); then
  echo "a is equal to b"
elif ((a > b)); then
  echo "a is greater than b"
else
  echo "a is less than b"
fi
