#!/bin/bash

# Exit with error if arguments are not specified
if [ $# -ne 2 ]; then 
    echo "Error: 2 arguments expected but $# specified"
    exit 1
fi 

# Set default directory
writefile="/tmp/aeld"

# Create directory specified in argument if specified
if [ $1 ]; then 
    writefile=$1
    mkdir -p $(dirname $writefile)
fi

# Create file with content
echo $2 > $writefile

# Exit with error if file could not be created
if [ ! -f $writefile ]; then
    echo "Error: Failed to create file at $writefile"
    exit 1
fi
