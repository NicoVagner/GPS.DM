#!/bin/bash

#   This script automatically converts GPS Day to yyy-mm-dd 
#   Uses dateConvert.x, found in the each search code directory

#Clean up
rm convertedGPSDays.txt
touch convertedGPSDays.txt

# Define the file containing GPS Days
numbers_file="GPSDays.txt"

# Define the output file
output_file="convertedGPSDays.txt"

# Specify the path to the directory containing the command file
command_directory="../Spring2023_Search_ESA/"

# Add an extra newline at the end of the numbers file
echo >> "$numbers_file"

# Run the command for each number in the file
while IFS= read -r number; do
  # Run the command and capture the console output
  output=$( "$command_directory/dateConvert.x" "$number" )
  
  # Extract the date portion from the output using string manipulation or regular expressions
  date=$(echo "$output" | grep -oE '[0-9]{4}-[0-9]{2}-[0-9]{2}')
  
  # Save the date to the output file
  echo "$date" >> "$output_file"
done < "$numbers_file"