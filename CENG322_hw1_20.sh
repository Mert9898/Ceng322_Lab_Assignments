#!/bin/bash
#250201017 Yağmur Nisa Şekerci
#260201011 Mert Ayaz Özkan

# Get the search directory from the user
read -p "Enter the name of the directory: " Directory

# Get the search keyword from the user
read -p "Enter the search keyword: " Keyword



function copy(){

	# Create the Found directory if it doesn't already exist
	if [ ! -d Found ]; then
    	mkdir Found
	fi

	# Loop through all the files in the search directory
	for file in "$Directory"/*
		do
    		# Check if the file contains the search keyword
    		if grep -q "$Keyword" "$file"; then
        		# Copy the file to the Found directory
        		cp "$file" Found/
        		echo "File '$file' was copied to the Found 			directory."
    		fi
		done

		# Check if any files were copied to the Found directory
		if [ "$(ls -A Found)" ]; then
    			echo "The following files were found:"
    			ls Found/
		else
    			echo "Keyword not found in files."
		fi
}



copy

function display_details(){



}
