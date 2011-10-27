#!/bin/bash
# Written by: Zachary Easterbrook
# Student ID: 103163420
# Written on: September 26th, 2011
#
# This program is designed to work
# exclusively with GNU sed. GNU sed
# offers the -i option which is used
# across EVERY linux distribution and
# is available on UNIX as gsed. We 
# require this version of sed because the -i
# option allows "in-place" editing of files,
# something that the pure UNIX version of sed
# lacks.
#
# with this in mind, please use this script on
# bravo.cs.uwindsor.ca, it is recognized to not work
# on charlie EXCEPT IN THE CASE OF REPLACING "sed"
# with "gsed" 

# This code has been tested on two different linux systems
# using the exact steps outlined in the assignment pdf
EXT=".java"
SRCDIR="project/src/uwindsor/cs256/"

oldname=$1
newname=$2
directory=$3

########## BEGIN DATA CHECKING ############
# It should be noted that Java class names
# are allowed to use unicode characters.
# This regular expression does not check for unicode
# characters therefore it is incomplete according to
# Java standards, however it does conform to the 
# outline given by the assignment and therefore 
# it is complete for our purposes.

if ! [[ "$newname" =~ ^[A-Za-z_][A-Za-z0-9_]*$ ]]; then
  echo "It appears you have an incorrectly formatted new class name."
  exit 1
fi

if [ "$directory" == "" ]; then
  directory="."
fi
########## AFTER THIS POINT ALL DATA IS CORRECT ############

########## BEGIN MAIN PROGRAM ############

# move the wrong class name to the correct one. We only do this for the file that
# has been specified by the assignment...it isn't too portable.
# A portable solution involves a for-each loop and finding all files in the directory
# then preforming the operations on each file.
mv $SRCDIR$oldname$EXT $SRCDIR$newname$EXT

# Find all files of type $EXT and execute the instruction
# sed -i "s/\<$oldname\>/$newname/g" {} \;
# this says "edit in place the file passed into {} and replace a string
# matching EXACTLY $oldname with the string $newname.
find $directory -name "*$EXT" -type f -exec sed -i "s/\<$oldname\>/$newname/g" {} \;

########## END MAIN PROGRAM ##############
