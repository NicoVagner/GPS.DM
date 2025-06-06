#!/bin/bash

#   The goal of this script is to pull the epochs out of 
#   each chiPEs file and organize the events by GPS day

#   Note that the chiPEs file saved in this directory are
#   initial search results only; parameter estimation needs to
#   be performed

#The results will be stored in the file specified be
rm initialEventEpochs.txt
touch initialEventEpochs.txt

#FILE=chiPEs/chiPEs12904.out
for FILE in chiPEs/chiPEs*; do

    #Gets date from file name
    date="${FILE:13:5}"

    #Save the first column of the file to an array 
    #Each array position is a different line of the first column
    declare -a firstColumn=()
    while read -r columnValue _; do
        firstColumn+=("$columnValue")
    done < "$FILE"

    #Converting the GPS Day to UTC
    dateConvert=$(/home/jitens/Spring2023_Search_ESA/./dateConvert.x $date)
    utcDate=$(echo "$dateConvert" | grep -oE '[0-9]{4}-[0-9]{2}-[0-9]{2}$')

    #Here I'm printing out the GPS Day followed by each epoch
    for epoch in "${firstColumn[@]}"; do
        printf '%s %s %s\n' "$date" "$utcDate" "$epoch" >> initialEventEpochs.txt
    done

done