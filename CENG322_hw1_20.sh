#!/bin/bash
#250201017 Yağmur Nisa Şekerci
#260201011 Mert Ayaz Özkan

echo "Enter the name of the directory:"
read directory

echo "Enter the keyword:"
read keyword

copy () {
    FOUND_FILES=$(grep -rl $keyword $directory)
    if [ "$FOUND_FILES" ]
        then
            if [ ! -d "Found" ]
				then
  					mkdir Found
			fi
			# Create the Found directory if it doesn't already exist
            for file in $FOUND_FILES
                do
					filename=$(basename "${file}")
					newname="Found_${filename}"
					# Copy file to Found directory with new name
					cp "${file}" "Found/${newname}"
                done
            echo "Files were copied to the Found directory!"
            ls Found
        else
            echo "Keyword not found in files!"
    fi
}

copy

modification_details(){
	num=0
	if [ -d "Found" ]
		then
			for file in "Found/"
				do
					modification=$(stat -c "File $num: %n was modified by %U on %y" "${file}")
					echo "${modification}"
					echo "${modification}" >> Found/modification_details.txt
					num=$((num+1))
				done
	fi
}

modification_details

