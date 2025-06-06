#!/bin/bash

#This bash script was written to run parameter estimaions automatically

#   Changing the values in "for i in {xxxx..yyyy}" will allow you to run a specific set of days
#   from the list provided in the "gpsdayFile.txt" document, a highlighted list of possible PE days.

#   The "epochFile.txt" document contains the associated epochs which correspond to those possible PE days

#gpsdayFile.txt example (append everything - including blank spaces - after the numbers) (exclude the # symbol)
#1282 0 1282 0        \| Week\/day range \(W1 D1 W2 D2\)            \(6\)

#to save a specified line to a variable
#gpsDay=`awk 'NR==1265' gpsdayFile.txt`
#epoch=`awk 'NR==1265' epochFile.txt`

#replacing a specific line with another line
#sed -i "6s|.*|$gpsDay|" search.dat
#sed -i "7s|.*|$epoch|" search.dat

#The below section is essential for the script to run, anything above here is just for reference!
for i in {1..4746} #for example, {1..100} will search through gpsdayFile.txt from line 1 to 100
do
    gpsDay=`awk 'NR==day' day="${i}" gpsdayFileJPL.txt` #be very careful with the formatting of this file! same with epochFile.txt
    #epoch=`awk 'NR==time' time="${i}" epochFile.txt` #needed if doing param. est.
    sed -i "6s|.*|$gpsDay|" search.dat
    #sed -i "7s|.*|$epoch|" search.dat #needed if doing param. est.

    #Add 15 minute delay so that the ESA files are fixed before search
    #sleep 60

    #Run the search, save console output to a file
    ./search.x > firstSearchResults/"$i".txt
done
