#!/bin/bash
#250201017 Yağmur Nisa Şekerci
#260201011 Mert Ayaz Özkan

read -p "Enter the name of the directory: " Directory
read -p "Enter the keyword: " Keyword

function copy(){
	
	mkdir /Found

	for _fl_ in "$Directory";do
		
	if[-f _f1_ && grep -r $Keyword _f1_];

		then
			cp $_f1_ "$Directory/Found"
			mv "$_f1_" "Found_ $_f1_"
			echo ("Files were copied to the Found directory!")
		else
			echo("Keyword not found in files!")

      fi

}

function display_details(){



}
