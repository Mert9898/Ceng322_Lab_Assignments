#!/bin/bash
#250201017 Yağmur Nisa Şekerci
#260201011 Mert Ayaz Özkan

echo "Enter the name of the directory:"
read directory

echo "Enter the keyword:"
read keyword

function copy(){

	# Create the Found directory if it doesn't already exist
	if [ ! -d "Found" ]; then
  		mkdir Found
	fi

	# Search for files containing keyword
	found=false

	for file in "${directory}/"*; 
	do
  		if grep -q "${keyword}" "${file}"; then
    			found=true
    			 filename=$(basename "${file}")
    			newname="Found_${filename}"
    			# Copy file to Found directory with new name
    			cp "${file}" "Found/${newname}"
  		fi
	done

	if [ $found == true ]; then
  		echo "Files copied to the Found directory!"
  		echo "Files in the Found directory:"
  		ls Found/
	else
  		echo "Keyword not found in files."
	fi
}

copy


function modification_details(){
	for file in "Found/"*; 
	
		do
  		modification=$(stat -c "File %n: %F was modified by %U on %y" "${file}")
		echo "${modification}"
  		echo "${modification}" >> Found/modification_details.txt
		done

}

modification_details

