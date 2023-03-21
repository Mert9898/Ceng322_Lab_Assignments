#!/usr/bin/bash
read -p "Enter the name of the directory: " Directory
read -p "Enter the keyword: " Keyword


copy () {
    FOUND_FILES=$(grep -rl $Keyword $Directory)
    if [ "$FOUND_FILES" ]
        then
            mkdir Found
            for f1 in $FOUND_FILES
                do
                    cp "$f1" "Found"
                done
            echo "Files were copied to the Found directory!"
            ls Found
        else
            echo "Keyword not found in files!"
    fi
}

copy