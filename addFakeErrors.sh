#!/bin/bash

#   The goal of this script is to append fake formal errors 
#   onto the end of each line of ESA clock data

#   The formal errors are very small and change slowly, so
#   the fake errors will all be the same.

#   The fake error will be 1.000000000000e-10 exactly

#Loop through all ESA files in the directory
for FILE in "jpl"*
do 
    line_number=0 #Reset the line_number for each file
    while read line
    do
        #Search for "END OF HEADER"
        ((line_number++))
        if [[ $line == *"END OF HEADER"* ]]
        then
            break
        fi
    done < $FILE

    #This is where the data begins
    startOfData=$((line_number + 1))
    echo $startOfData

    # Create a new file for the modified content
    output_file="${FILE}_modified"
    touch $output_file

    # Loop through each line in the input file
    count=1
    while IFS= read -r line; do
    if [ $count -ge $startOfData ]; then
        # Remove 21 blank spaces from the end of the line
        trimmed_line=$(echo "$line" | sed 's/ \{21\}$//')
        echo "$trimmed_line" >> $output_file
    else
        # Copy the line as-is to the output file
        echo "$line" >> $output_file
    fi
    count=$((count+1))
    done < "$FILE"

    
    output_file="${FILE}_modified"

    # create a new filename to save the modified data
    newFilename="${output_file}_fixed"

    # copy the lines before the startOfData to the new file
    head -n $((startOfData - 1)) "${output_file}" > "${newFilename}"

    # loop through each line starting from line 193 and modify it
    lineNum=$startOfData
    while read -r line; do
    # add two spaces and 1.000000000000e-10 to the beginning of each line
    modifiedLine="${line}  1.000000000000e-10"
    # append the modified line to the new file
    echo "${modifiedLine}" >> "${newFilename}"
    lineNum=$((lineNum + 1))
    done < <(tail -n +${startOfData} "${output_file}")

    echo "Modified file saved as ${newFilename}"

done