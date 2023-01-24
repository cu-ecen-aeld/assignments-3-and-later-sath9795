#!/bin/bash

#Checking the number of parameters
if [ "$#" -ne 2 ]; then 
  echo "Error: Two parameters required. Exiting."
  exit 1
fi

#Checking if the first parameter is a directory
if [ ! -d "$1" ]; then
  echo "Error: First argument must be an existing directory. Exiting."
  exit 1
fi

#Setting variables
filesdir="$1"
searchstr="$2"

#Finding all the files in the directory
files=$(find "$filesdir" -type f)

#Counting the number of files
num_files=$(echo "$files" | wc -l)

#Finding the number of matching lines
matches=$(grep -r "$searchstr" "$filesdir")
num_matches=$(echo "$matches" | wc -l)

#Printing the output
echo "The number of files are $num_files and the number of matching lines are $num_matches"
