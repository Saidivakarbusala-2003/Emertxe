/*
Name        : Busala Sai Divakar.

Date        : 08-02-2026.

Project     : Mp3 Tag Reader & Editor in C.

Description : Mp3 tag reader and editor application

This application allows users to view and edit ID3 tags of mp3 files. 
It supports viewing tags such as title, artist, album, year, and genre, 
as well as editing these tags with new information provided by the user.

mp3 Tag Reader & Editor is a command-line application developed in the C programming
language that enables users to efficiently read and modify ID3 tags in mp3 files. 
The project demonstrates the use of file handling, string operations, 
memory management, and modular programming concepts in C.
*/  

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "reader.h"
#include "edit.h"
#include "header.h"

int main(int argc,char* argv[]) //main function to handle command line arguments and call appropriate functions based on user input
{                             
    if(argc <= 1 || argc > 6) //check if the number of arguments is less than or equal to 1 or greater than 6
    {
        display_error(); //display error message if the number of arguments is invalid and return 1
        return 1;    
    }

    else if(strstr(argv[1],"--help") != 0) //check if the first argument is "--help", if it is, display help menu
    {
        help_menu();//display help menu and return 0
        return 0;
    }

    else if (strcmp(argv[1], "-v") == 0) //check if the first argument is "-v" (view option)
    {
        if (argc != 3) //check if the number of arguments is not equal to 3 (program name, view option, and mp3 file name)
        {
            display_error(); //display error message
            return 1;
        }

        if (!check_file_exists(argv[2])) //check if the file specified in the second argument does not exist
        {
            printf("ERROR: Unable to locate file: %s\n", argv[2]); //print error message if the file does not exist
            printf("Please provide a valid mp3 file name ! Only support mp3 files\n"); //print error message for invalid file
            return 1;
        }

        view_tags(argv[2]); //call function to view tags of the specified mp3 file
        return 0;
    }

    else if (strcmp(argv[1], "-e") == 0) //check if the first argument is "-e" (edit option)
    {
        if (argc != 5) //check if the number of arguments is not equal to 5 (program name, edit option, tag to edit, new data, and mp3 file name)
        {
            display_error(); //display error message if the number of arguments is invalid and return 1
            return 1; 
        }

        char *tag = argv[2]; //store the tag to edit from the second argument (e.g., -t for title, -a for artist, etc.)
        char *new_data = argv[3]; //store the new data to be written into the tag from the third argument
        char *filename = argv[4]; //store the mp3 file name from the fourth argument

        if (!check_file_exists(filename)) //check if the specified mp3 file does not exist
        {
            printf("ERROR: Unable to locate file: %s\n", filename); //print error message if the file does not exist
            printf("Please provide a valid mp3 file name ! Only support mp3 files\n"); //print error message for invalid file
            return 1;
        }

        if (edit_tag(filename, tag, new_data) != 0) //check if the edit_tag function returns a non-zero value (indicating an error)
        {
            perror("Failed to edit tag"); //print error message if editing the tag fails and return 1
            return 1;
        }

        printf("Tag edited successfully.\n"); //print success message if the tag is edited successfully and return 0
        return 0;
    }
    else
    {
        display_error(); //display error message if the first argument is not "-v", "-e", or "--help"
        return 1;
    }
    return 0;  
}



