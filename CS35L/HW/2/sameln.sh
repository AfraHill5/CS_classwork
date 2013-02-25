#!/bin/bash

if [ -d $1 ]; then

	#temp1=`ls -A -1 $1 | grep '^\.'`
	#temp2=`ls -1 $1`

	#all=$temp1"\n"$temp2

	all=`ls -A -1 $1 | grep '^\.'; ls -1 $1`

	echo -e $all
	declare -a fileArray
	let count=0

	#for file in $all; do
	echo "$all" > temp.txt
	while read file
	do
		if [ -f "$1/$file" ]; then
			echo "$1/$file is a regular file."
		
		fileArray[$count]="$1/$file"
			let count=count+1
			echo $count
		else
			echo "$1/$file is not a regular file."
		fi
	done < temp.txt
	rm temp.txt
	echo "$count files found."

	for ((x=0; x<$count; x++)); do

		for ((y=x+1; y<$count; y++)); do

			cmp -s "${fileArray[$x]}" "${fileArray[$y]}"
			if [ $? -eq 0 ]; then
				ln "${fileArray[$x]}" "${fileArray[$y]}"
				fileArray[$y]=fileArray[$x] #overwrites the array element to prevent duplicates
			fi
		done
	done


else
	echo "Directory does not exist!"
fi
